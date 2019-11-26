#include <emmintrin.h>
#include <game/game.h>

namespace  {
    std::shared_ptr<ResourceFile> graphic_resources;
    std::vector<std::shared_ptr<SOASpriteRGB>> tiles[4] = {
        std::vector<std::shared_ptr<SOASpriteRGB>>{},
        std::vector<std::shared_ptr<SOASpriteRGB>>{},
        std::vector<std::shared_ptr<SOASpriteRGB>>{},
        std::vector<std::shared_ptr<SOASpriteRGB>>{}
    };

    uint32_t mouse_x;
    uint32_t mouse_y;
}

namespace Game {
    namespace GameStage {
        ecs_hpp::registry world;
        uint8_t*          terrain_cache;
        GameStageShared   shared;
    }

    namespace MainMenuStage {
        ecs_hpp::registry world;
    }

    namespace CityStage {
        ecs_hpp::registry world;
    }

    GLFWwindow* glfw_window;

    uint16_t window_width = 1024;
    uint16_t window_height = 768;
    bool windowed = false;

    void init() {
        try {
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

            graphic_resources = std::make_shared<ResourceFile>("GRAPHICS.res");
            {
                auto [success, units_reg_file] = graphic_resources->read_registry_res_unique("units/units.reg");
                if(success) {
                    LOG("registry succesfully loaded from resource");
                    auto [files_found, files_value] = units_reg_file->get_string("Files/File0");
                    if(files_found) {
                        LOG("Found Files/File0 entry of type string with a value of \"" << files_value << "\"");
                    }

                    auto [desc_text, id] = units_reg_file->read_record(
                        "Unit14/",
                        StringField{"DescText"}, IntField{"ID"});
                    LOG("variadic template read returned [desc_text = " << desc_text << ", ID = " << id << "]");

                    auto reg_entry = units_reg_file->read_record2(
                        "Unit14/",
                        StringField{"DescText"},
                        IntField{"ID"}
                    );
                    LOG("count of names: " << reg_entry.field_count);
                    LOG("names:");
                    for(size_t i = 0; i < reg_entry.field_count; ++i) {
                        LOG("    " << reg_entry.field_names[i]);
                    }
                }
            }

            {
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
        } catch (const std::exception& ex) {
            LOG_ERROR(ex.what());
        }
    }

    void update(double delta_time) {

    }

    void render(SOASpriteRGB &background_sprite) {
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
            initiate_game_closing();
        }
    }

    void mouse_button_callback(
        GLFWwindow* window,
        int button,
        int action,
        int mods
    ) {
//        LOG("Got mouse event: "<<
//            "[button=" << button << "], " <<
//            "[action=" << action << "], " <<
//            "mods=" << mods << "]");
    }

    void mouse_callback(
        GLFWwindow* window,
        double xpos,
        double ypos
    ) {
//        LOG("Mouse position: [" << xpos << ", " << ypos << "]");
        mouse_x = static_cast<uint32_t>(xpos);
        mouse_y = static_cast<uint32_t>(ypos);
    }

    void initiate_game_closing() {
        glfwSetWindowShouldClose(glfw_window, true);
    }
}



