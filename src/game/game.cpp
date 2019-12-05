#include <emmintrin.h>
#include <game/game.h>
#include <game/main_menu_stage.h>
#include <game/character_generation_stage.h>
#include <game/cursor_subsystem.h>
#include <game/cursor_state.h>
#include <loaders/ksy/rage_of_mages_1_txt_866.h>
#include <graphics/font_rendering.h>
#include <graphics/Sprite256.h>
#include <queue>

const double GAME_SPEED_MS[9] = {0.180, 0.130, 0.090, 0.060, 0.040, 0.035, 0.030, 0.025, 0.020};

namespace  {
    enum class game_state {
        main_menu,
        character_generation,
        city,
        shop,
        inn,
        training_center,
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

    std::shared_ptr<Font16> test_font;
    std::shared_ptr<Font16a> test_font2;
    std::string lalala;
    std::shared_ptr<Sprite256> goblin_sprite;

    double tick_accumulator;
    double cursor_tick_accumulator;
    const uint8_t cursor_speed = 4;
    uint8_t game_speed;
    uint16_t cursor_frame;

    game_state current_game_state;

    Game::MouseState mouse_state;
}

namespace Game {

    static std::unique_ptr<CursorSubsystem> cursor_subsystem;

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
        Game::dispatch_message(event::set_cursor, static_cast<uint8_t>(cursor_state::c_select));
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
        Game::dispatch_message(event::set_cursor, static_cast<uint8_t>(cursor_state::c_default));
        request_clear();
    }

    void init() {
        try {
            double mouse_x_initial;
            double mouse_y_initial;

            glfwGetCursorPos(glfw_window, &mouse_x_initial, &mouse_y_initial);

            mouse_state.mouse_x = static_cast<uint16_t>(mouse_x_initial);
            mouse_state.mouse_y = static_cast<uint16_t>(mouse_y_initial);

            tick_accumulator = 0.0;
            cursor_tick_accumulator = 0.0;
            cursor_frame = 0;
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

            auto [gb_result, gb_sprite] = graphic_resources->read_256_shared("units/monsters/goblin/sprites.256");
            goblin_sprite = gb_sprite;


//            {
//                auto [success, scenario_reg_file] = scenario_resources->read_registry_res_unique("scenario.reg");
//                if(!success) {
//                    LOG_ERROR("scenario.reg not found");
//                }

//                auto [total_missions, scenario_mission, mercenary_count] =
//                    scenario_reg_file->read_record(
//                        "General/",
//                        IntField{"TotalMissions"},
//                        IntField{"ScenarioMission"},
//                        IntArrayField{"MercenaryCount"}
//                    );
//                if(scenario_mission.exists) {
//                    LOG("game considered finish if mission " << scenario_mission.content << " complete");
//                }

//                if(total_missions.exists) {
//                    char buf[16];

//                    LOG("game has " << total_missions.content << " main missions");

//                    std::queue<uint8_t> missions;
//                    for(uint8_t i = 1; i <= total_missions.content; ++i ) {
//                        missions.push(i * 10);
//                    }

//                    while(!missions.empty()) {
//                        auto next_mission = missions.front();
//                        missions.pop();
//                        sprintf(buf, "Mission%u/", next_mission);
//                        std::cout << buf << std::endl;
//                        auto [
//                            mercenaries,
//                            inn_npcs,
//                            inn_missions,
//                            add_text_documents,
//                            shop_min_price,
//                            shop_max_price,
//                            enable_mercenaries,
//                            payment,
//                            tc_mission,
//                            add_picture_docums,
//                            auto_get_mission,
//                            shop_mission
//                        ] = scenario_reg_file ->read_record(buf,
//                            IntArrayField{"Mercenaries"},
//                            IntArrayField{"InnNPC"},
//                            IntArrayField{"InnMission"},
//                            IntArrayField{"AddTextDocument"},
//                            IntField{"ShopMinPrice"},
//                            IntField{"ShopMaxPrice"},
//                            IntArrayField{"EnableMercenary"},
//                            IntField{"Payment"},
//                            IntField{"TCMission"},
//                            IntArrayField{"AddPictureDocum"},
//                            IntField{"AutoGetMission"},
//                            IntField{"ShopMission"}
//                        );
//                        if(auto_get_mission.exists) std::cout << "    auto get mission: " << auto_get_mission.content << std::endl;
//                        if(shop_mission.exists){
//                            if(shop_mission.content != 0 && shop_mission.content != next_mission) {
//                                missions.push(static_cast<uint8_t>(shop_mission.content));
//                            }
//                            std::cout << "    shop mission: " << shop_mission.content << std::endl;
//                        }
//                        if(tc_mission.exists){
//                            if(tc_mission.content != 0 && tc_mission.content != next_mission) {
//                                missions.push(static_cast<uint8_t>(tc_mission.content));
//                            }
//                            std::cout << "    training center mission: " << tc_mission.content << std::endl;
//                        }
//                        if(shop_min_price.exists) std::cout << "    shop min price: " << shop_min_price.content << std::endl;
//                        if(shop_max_price.exists) std::cout << "    shop max price: " << shop_max_price.content << std::endl;
//                        if(payment.exists) std::cout << "    payment: " << payment.content << std::endl;
//                        if(inn_missions.exists) {
//                            std::cout << "    inn missions:" << std::endl;
//                            for(auto mission_entry : inn_missions.content) {
//                                if(mission_entry != 0 && mission_entry != next_mission) {
//                                    missions.push(static_cast<uint8_t>(mission_entry));
//                                }
//                                std::cout << "        " << mission_entry << std::endl;
//                            }
//                        }
//                        if(inn_npcs.exists) {
//                            std::cout << "    inn npcs:" << std::endl;
//                            for(auto npc_entry : inn_npcs.content) {
//                                std::cout << "        " << npc_entry << std::endl;
//                            }
//                        }
//                        if(add_text_documents.exists) {
//                            std::cout << "    add text documents:" << std::endl;
//                            for(auto entry : add_text_documents.content) {
//                                std::cout << "        " << entry << std::endl;
//                            }
//                        }
//                        if(add_picture_docums.exists) {
//                            std::cout << "    add picture documents:" << std::endl;
//                            for(auto entry : add_picture_docums.content) {
//                                std::cout << "        " << entry << std::endl;
//                            }
//                        }
//                        if(mercenaries.exists) {
//                            std::cout << "    mercenaries:" << std::endl;
//                            for(auto entry : mercenaries.content) {
//                                std::cout << "        " << entry << std::endl;
//                            }
//                        }
//                        if(enable_mercenaries.exists) {
//                            std::cout << "    enable mercenaries:" << std::endl;
//                            for(auto entry : enable_mercenaries.content) {
//                                std::cout << "        " << entry << std::endl;
//                            }
//                        }
//                    }
//                }
//            }

            auto event10res = main_resources->get_resource("text/battle/m10/event01.txt");
            auto event10bytes = event10res->bytes();
            kaitai::kstream ks{event10bytes};
            rage_of_mages_1_txt_866_t txt{&ks};

            lalala = txt.content();

            auto [font_success, font] = graphic_resources->read_font_16_shared("font1/font1.16", "font1/font1.dat");
            if(!font_success) {
                throw std::runtime_error("failed on loading font");
            }
            test_font = font;

            auto [font2_success, font2] = graphic_resources->read_font_16a_shared("font5/font5.16a", "font5/font5.dat");
            if(!font2_success) {
                throw std::runtime_error("failed on loading font");
            }
            test_font2 = font2;

            cursor_subsystem = std::make_unique<CursorSubsystem>(graphic_resources, cursor_state::c_move);

            load_main_menu_assets();
            load_terrain_tiles();
            set_main_menu_state();

        } catch (const std::exception& ex) {
            LOG_ERROR(ex.what());
            abort();
        }
    }

    void update(double delta_time) {
        tick_accumulator += delta_time;
        cursor_tick_accumulator += delta_time / 4.0;
        while(cursor_tick_accumulator > GAME_SPEED_MS[cursor_speed]) {
            cursor_tick_accumulator -= GAME_SPEED_MS[cursor_speed];
            cursor_subsystem->update();
        }
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
        if(current_game_state != game_state::game) {
            // ^^^ in the case of game_state::game all screen
            // will be garantilly entirely refilled anyway,
            // so this filter is some sort of optimization
            background_sprite.lock([&](auto w, auto h, auto rbuf, auto gbuf, auto bbuf) {
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

        //cursor_rendering

        cursor_subsystem->render(background_sprite, mouse_state);

        test_font2->render_text(lalala, background_sprite, 16, 16);
        goblin_sprite->blit_on_sprite(background_sprite, 0, 0, 10);
    }

    void key_callback(
        GLFWwindow* window,
        int key,
        int scancode,
        int action,
        int mods
    ) {
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
        switch (action) {
            case GLFW_PRESS:{
                    switch (button) {
                        case 0: mouse_state.left_button_down = true; break;
                        case 1: mouse_state.middle_button_down = true; break;
                        case 2: mouse_state.right_button_down = true; break;
                    }
                }
                break;
            case GLFW_RELEASE:{
                    switch (button) {
                        case 0: mouse_state.left_button_down = false; break;
                        case 1: mouse_state.middle_button_down = false; break;
                        case 2: mouse_state.right_button_down = false; break;
                    }
                }
                break;
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
            default: break;
        }
    }

    void dispatch_message(const event& message, uint8_t param) {
        switch (message) {
            case event::set_cursor:
                cursor_subsystem->set_cursor(static_cast<cursor_state>(param));
                break;
            default: break;
        }

    }

    void dispatch_message(const event& message, uint8_t param0, uint8_t param1) {

    }
}
