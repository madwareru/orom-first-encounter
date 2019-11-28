#include <emmintrin.h>
#include <game/game.h>
#include <game/main_menu_stage.h>
#include <game/character_generation_stage.h>

const double GAME_SPEED_MS[9] = {0.180, 0.130, 0.090, 0.060, 0.040, 0.035, 0.030, 0.025, 0.020};

namespace  {
    enum class game_state {
        main_menu,
        character_generation,
        city,
        game
    };

    std::shared_ptr<ResourceFile> graphic_resources;
    std::shared_ptr<ResourceFile> main_resources;
    std::shared_ptr<ResourceFile> movie_resources;
    std::shared_ptr<ResourceFile> scenario_resources;
    std::shared_ptr<ResourceFile> sfx_resources;
    std::shared_ptr<ResourceFile> speech_resources;
    std::shared_ptr<ResourceFile> world_resources;

    const char* GRAPHICS_RES_FILENAME = "GRAPHICS.res";
    const char* MAIN_RES_FILENAME     = "MAIN.res";
    const char* MOVIES_RES_FILENAME   = "MOVIES.res";
    const char* SCENARIO_RES_FILENAME = "SCENARIO.res";
    const char* SFX_RES_FILENAME      = "SFX.res";
    const char* SPEECH_RES_FILENAME   = "SPEECH.res";
    const char* WORLD_RES_FILENAME    = "WORLD.res";

    std::vector<std::shared_ptr<SOASpriteRGB>> tiles[4] = {
        std::vector<std::shared_ptr<SOASpriteRGB>>{},
        std::vector<std::shared_ptr<SOASpriteRGB>>{},
        std::vector<std::shared_ptr<SOASpriteRGB>>{},
        std::vector<std::shared_ptr<SOASpriteRGB>>{}
    };

    double tick_accumulator;
    uint8_t game_speed;

    game_state current_game_state;

    Game::MouseState mouse_state;
}

namespace Game {

    namespace GameStage {
        ecs_hpp::registry world;
        uint8_t*          terrain_cache;
        GameStageShared   shared;
    }

    namespace MainMenuStage {
        static std::unique_ptr<Stage> stage;
    }

    namespace CharacterGenerationStage {
        static std::unique_ptr<Stage> stage;
        static bool assets_loaded;
    }

    namespace CityStage {
        ecs_hpp::registry world;
    }

    bool clear_made;

    GLFWwindow* glfw_window;

    uint16_t window_width = 1024;
    uint16_t window_height = 768;
    bool windowed = false;
    uint8_t clear_r;
    uint8_t clear_g;
    uint8_t clear_b;

    void request_clear() {
        clear_made = false;
    }

    void load_main_menu_assets() {
        using namespace MainMenuStage;
        stage = std::make_unique<Stage>(main_resources, window_width, window_height);
    }

    void load_character_generation_assets() {
        using namespace CharacterGenerationStage;
        stage = std::make_unique<Stage>(graphic_resources, window_width, window_height);
    }

    void load_terrain_tiles() {
        char buf[32];
        for(size_t i = 1; i <= 4; ++i) {
            const size_t capacity = (i < 4) ? 16 : 4;
            tiles[i-1].reserve(capacity);
            for(size_t j = 0; j < capacity; ++j)
            {
                if(j < 10) {
                    sprintf(buf, "terrain/tile%d-0%d.bmp", (int)i, (int)j);
                } else {
                    sprintf(buf, "terrain/tile%d-%d.bmp", (int)i, (int)j);
                }
                auto[success, next_bmp] = graphic_resources->read_bmp_shared(buf);
                if(success) {
                    tiles[i-1].emplace_back(next_bmp);
                }
            }
        }
    }

    void set_main_menu_state() {
        using namespace MainMenuStage;
        stage->on_enter();
        current_game_state = game_state::main_menu;
        request_clear();
    }

    void set_char_gen_state() {
        using namespace CharacterGenerationStage;
        if(!assets_loaded) {
            load_character_generation_assets();
            assets_loaded = true;
        }
        stage->on_enter();
        current_game_state = game_state::character_generation;
        request_clear();
    }

    void init() {
        try {
            tick_accumulator = 0.0;
            game_speed = 4;

            size_t offset = 0;

            GameStage::shared.terrain_tile_x_cache = &GameStage::terrain_cache[offset];
            offset += window_width * window_height;
            GameStage::shared.terrain_tile_y_cache = &GameStage::terrain_cache[offset];
            offset += window_width * window_height;
            GameStage::shared.terrain_tile_u_cache = &GameStage::terrain_cache[offset];
            offset += window_width * window_height;
            GameStage::shared.terrain_tile_v_cache = &GameStage::terrain_cache[offset];
            GameStage::shared.camera_x = 0;
            GameStage::shared.camera_y = 0;

            graphic_resources  = std::make_shared<ResourceFile>(GRAPHICS_RES_FILENAME);
            main_resources     = std::make_shared<ResourceFile>(MAIN_RES_FILENAME);
            movie_resources    = std::make_shared<ResourceFile>(MOVIES_RES_FILENAME);
            scenario_resources = std::make_shared<ResourceFile>(SCENARIO_RES_FILENAME);
            sfx_resources      = std::make_shared<ResourceFile>(SFX_RES_FILENAME);
            speech_resources   = std::make_shared<ResourceFile>(SPEECH_RES_FILENAME);
            world_resources    = std::make_shared<ResourceFile>(WORLD_RES_FILENAME);

            CharacterGenerationStage::assets_loaded = false;

            load_main_menu_assets();
            load_terrain_tiles();
            set_main_menu_state();

            {
                auto [success, units_reg_file] = graphic_resources->read_registry_res_unique("units/units.reg");
                if(success) {
                    auto [desc_text, id] = units_reg_file->read_record(
                        "Unit14/",
                        StringField{"DescText"}, IntField{"ID"});

                    LOG("desc_text exists? " << desc_text.exists <<
                        "\nID exists? " << id.exists);

                    LOG("[desc_text = " << desc_text.content <<
                        ", ID = " << id.content << "]");
                }
            }

        } catch (const std::exception& ex) {
            LOG_ERROR(ex.what());
            abort();
        }
    }

    void update(double delta_time) {
        tick_accumulator += delta_time;
        while (tick_accumulator > GAME_SPEED_MS[game_speed]) {
            tick_accumulator -= GAME_SPEED_MS[game_speed];
            switch (current_game_state) {
                case game_state::main_menu:
                    MainMenuStage::stage->update(mouse_state);
                    break;
                case game_state::character_generation:
                    CharacterGenerationStage::stage->update(mouse_state);
                    break;
                default:
                    break;
            }
        }
    }

    void render_city(SOASpriteRGB &background_sprite) {

    }

    void render_game(SOASpriteRGB &background_sprite) {
        size_t x = 0;
        size_t y = 0;
        for(auto tileset : tiles) {
            for(auto tile : tileset) {
                tile->blit_on_sprite(background_sprite, x, y);
                x += 32;
                if(x >= 1024) {
                    x %= 1024;
                    y += 32 * 14;
                }
            }
        }
    }

    void render(SOASpriteRGB &background_sprite) {
        if(!clear_made) {
            background_sprite.mutate([&](auto w, auto h, auto rbuf, auto gbuf, auto bbuf) {
                const size_t size = w * h;
                __m128i clrr = _mm_set1_epi8(static_cast<int8_t>(clear_r));
                __m128i clrg = _mm_set1_epi8(static_cast<int8_t>(clear_g));
                __m128i clrb = _mm_set1_epi8(static_cast<int8_t>(clear_b));

                uint8_t *rb = rbuf;
                uint8_t *gb = gbuf;
                uint8_t *bb = bbuf;

                for(size_t i = size / 16; i; --i) {
                    _mm_stream_si128(reinterpret_cast<__m128i*>(bb), clrb);
                    _mm_stream_si128(reinterpret_cast<__m128i*>(gb), clrg);
                    _mm_stream_si128(reinterpret_cast<__m128i*>(rb), clrr);
                    rb += 16;
                    gb += 16;
                    bb += 16;
                }
            });
            clear_made = true;
        }

        switch (current_game_state) {
            case game_state::main_menu:
                MainMenuStage::stage->render(background_sprite);
                break;
            case game_state::character_generation:
                CharacterGenerationStage::stage->render(background_sprite);
                break;
            case game_state::city:
                render_city(background_sprite);
                break;
            case game_state::game:
                render_game(background_sprite);
                break;
        }
    }

    void key_callback(
        GLFWwindow* window,
        int key,
        int scancode,
        int action,
        int mods
    ) {
//        LOG("Got key event: "<<
//            "[key=" << key << "], " <<
//            "[scancode=" << scancode << "], " <<
//            "[action=" << action << "], " <<
//            "mods=" << mods << "]");
        if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
            Game::dispatch_message(Game::event::close_game);
        }
    }

    void mouse_button_callback(
        GLFWwindow* window,
        int button,
        int action,
        int mods
    ) {
        if(button == 0 && action == GLFW_PRESS) {
            mouse_state.left_button_down = true;
        }
        else if(button == 0 && action == GLFW_RELEASE) {
            mouse_state.left_button_down = false;
        }
        else if(button == 1 && action == GLFW_PRESS) {
            mouse_state.middle_button_down = true;
        }
        else if(button == 1 && action == GLFW_RELEASE) {
            mouse_state.middle_button_down = false;
        }
        else if(button == 2 && action == GLFW_PRESS) {
            mouse_state.right_button_down = true;
        }
        else if(button == 2 && action == GLFW_RELEASE) {
            mouse_state.right_button_down = false;
        }
    }

    void mouse_callback(
        GLFWwindow* window,
        double xpos,
        double ypos
    ) {
        mouse_state.mouse_x = static_cast<uint16_t>(xpos);
        mouse_state.mouse_y = static_cast<uint16_t>(ypos);
    }

    void initiate_game_closing() {
        glfwSetWindowShouldClose(glfw_window, true);
    }

    void dispatch_message(const event& message) {
        switch (message) {
            case event::close_game:
                initiate_game_closing();
                break;
            case event::start_new_game:
                set_char_gen_state();
                break;
            case event::goto_main_menu:
                set_main_menu_state();
                break;
        }
    }

    void dispatch_message(const event& message, uint8_t param) {

    }


    void dispatch_message(const event& message, uint8_t param0, uint8_t param1) {

    }
}
