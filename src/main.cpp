#include <iostream>
#include <fstream>
#include <emmintrin.h>
#include <vector>

#include <globals/globals.h>

#include <windowing/window.h>

#include <util/defer_action.h>
#include <util/macro_shared.h>

#include <graphics/framebuffer.h>
#include <graphics/soaspritergb.h>
#include <graphics/soaspritergba.h>

#include <loaders/pngloader.h>
#include <loaders/resource_file.h>
#include <loaders/registry_file.h>

namespace  {
    std::shared_ptr<ResourceFile> graphic_resources;
    std::vector<std::shared_ptr<SOASpriteRGB>> tiles[4];

    void init() {
        graphic_resources = std::make_shared<ResourceFile>("graphics.res");

        { // here we should be able to safely retrieve resource file as a registry and read string value from it
            auto [success, units_reg_file] = graphic_resources->read_registry_res("units/units.reg");
            DEFER_CLEANUP(units_reg_file);
            if(success) {
                LOG("registry succesfully loaded from resource");
                auto [files_found, files_value] = units_reg_file->get_string("Files/File0");
                if(files_found) {
                    LOG("Found Files/File0 entry of type string with a value of \"" << files_value << "\"");
                }
            } else {
                LOG_ERROR("this is not a registry resource");
            }
        }

        {
            char buf[32];
            for(size_t i = 1; i <= 4; ++i) {
                const size_t capacity = (i < 4) ? 16 : 4;
                tiles[i-1].reserve(capacity);
                try {
                    for(size_t j = 0; j < capacity; ++j)
                    {
                        if(j < 10) {
                            sprintf(buf, "terrain/tile%d-0%d.bmp", (int)i, (int)j);
                        } else {
                            sprintf(buf, "terrain/tile%d-%d.bmp", (int)i, (int)j);
                        }
                        tiles[i-1].emplace_back(graphic_resources->read_bmp_shared(buf));
                    }
                } catch (const std::exception& ex) {
                    LOG_ERROR(ex.what());
                }
            }
        }
    }

    void update(double delta_time) {

    }

    void render(SOASpriteRGB& background_sprite) {
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
}

int main() {
    WindowCreationParams window_params {
        "Open Rage Of Mages", // title
        1024,                 // width
        768,                  // height
        false,                // fullscreen
        0x07, 0x02, 0x13      // clear color
    };

    LifetimeProcHolder lifetime_procs {
        init,
        update,
        render
    };

    using callback_holder = std::variant<
        KeyCallbackHolder,
        CursorPosCallbackHolder,
        MouseButtonCallbackHolder>;

    std::vector<callback_holder> eventCallbacks;

    if(!glfwInit()) {
        return 1;
    }

    GLFWwindow* glfw_window = INIT_WINDOW(window_params);

    if(!glfw_window) {
        return 1;
    }

    DEFER([&](){ glfwDestroyWindow(glfw_window); })

    if(!start_main_loop(
        glfw_window,
        window_params,
        lifetime_procs,
        eventCallbacks
    )) return 1;

    return 0;
}
