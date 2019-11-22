#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <graphics/framebuffer.h>
#include <graphics/soaspritergb.h>
#include <graphics/soaspritergba.h>
#include <loaders/pngloader.h>
#include <emmintrin.h>
#include <vector>

#include <loaders/resource_file.h>
#include <loaders/registry_file.h>
#include <util/defer_action.h>
#include <util/macro_shared.h>
#include <globals/globals.h>
#include <windowing/window.h>

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
        "Open Rage Of Mages",
        1024,
        768,
        false,
        0x40, 0x40, 0x40,
        &init,
        &update,
        &render
    };

    GLFWwindow* glfw_window;

    if(!glfwInit()) {
        return 1;
    }

    glfw_window = glfwCreateWindow(
        window_params.w_width,
        window_params.w_height,
        window_params.window_name,
        window_params.fullscreen ? glfwGetPrimaryMonitor() : nullptr,
        nullptr
    );

    if(!glfw_window) {
        return 1;
    }

    glfwSetWindowSizeLimits(
        glfw_window,
        window_params.w_width,
        window_params.w_height,
        window_params.w_width,
        window_params.w_height
    );

    if(!start_window(glfw_window, window_params)) return 1;

    glfwDestroyWindow(glfw_window);
    return 0;
}
