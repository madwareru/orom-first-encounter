#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "framebuffer.h"
#include "soaspritergb.h"
#include "soaspritergba.h"
#include "loaders/pngloader.h"
#include <emmintrin.h>
#include <vector>

#include "loaders/resource_file.h"
#include "loaders/registry_file.h"
#include "defer_action.h"
#include "macro_shared.h"
#include "globals/globals.h"

#define WIN_TITLE "Software rendering bootstrap"
#define WIN_W 1024
#define WIN_H 768
#define FPS_60_MILLIS 0.0166
#define FULLSCREEN false
#define VSYNC_ON

namespace  {
    GLFWwindow* glfw_window;
    HWND h_window;
    HDC h_dc;
    char title_buf[255];
    FrameBuffer frame_buffer{WIN_W, WIN_H};
    SOASpriteRGB sprite{WIN_W, WIN_H};
    std::shared_ptr<ResourceFile> graphic_resources;
    std::vector<std::shared_ptr<SOASpriteRGB>> tiles[4];
}

void init();
void update(double);
void render();

void draw_back_on_device();
void clear_back(uint8_t r, uint8_t g, uint8_t b);

int main() {
    if(!glfwInit()) {
        return EXIT_FAILURE;
    }

    glfw_window = glfwCreateWindow(WIN_W, WIN_H, WIN_TITLE " 60 fps", FULLSCREEN ? glfwGetPrimaryMonitor() : nullptr, nullptr);
    if(!glfw_window) {
        return EXIT_FAILURE;
    }

    h_window = glfwGetWin32Window(glfw_window);
    h_dc = GetDC(h_window);

    //glfwSetKeyCallback(glfw_window, &key_callback);
    //glfwSetCursorPosCallback(glfw_window, &cursor_position_callback);
    //glfwSetMouseButtonCallback(glfw_window, &mouse_button_callback);
    //glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    //glfwSetWindowIcon(glfw_window, 1, &icon_image);
    glfwSetWindowSizeLimits(glfw_window, WIN_W, WIN_H, WIN_W, WIN_H);

    double prev_time = glfwGetTime();
    double last_frame_gtime = glfwGetTime();
    int32_t fps = 0;

    init();

    while(!glfwWindowShouldClose(glfw_window)) {
        double global_time = glfwGetTime();
        double delta_time = global_time - last_frame_gtime;
        if(global_time - prev_time >= 1.0) {
            sprintf(title_buf, WIN_TITLE " %d fps", fps);
            glfwSetWindowTitle(glfw_window, title_buf);
            fps = 0;
            prev_time = global_time;
        } else {
            ++fps;
        }

#ifdef VSYNC_ON
        double point_a = glfwGetTime();
#endif
        update(delta_time);
        render();
#ifdef VSYNC_ON
        double diff = point_a + FPS_60_MILLIS - glfwGetTime();
        while(diff > 0.0) {
            glfwWaitEventsTimeout(diff);
            diff = point_a + FPS_60_MILLIS - glfwGetTime();
        }
#else
        glfwPollEvents();
#endif
        last_frame_gtime = global_time;
    }

    glfwDestroyWindow(glfw_window);
    return 0;
}

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

void render() {
    clear_back(0x40, 0x40, 0x40);
    size_t x = 0;
    size_t y = 0;
    for(auto tileset : tiles) {
        for(auto tile : tileset) {
            tile->blit_on_sprite(sprite, x, y);
            x += 32;
            if(x >= 1024) {
                x %= 1024;
                y += 32 * 14;
            }
        }
    }
    draw_back_on_device();
}


void clear_back(uint8_t r, uint8_t g, uint8_t b) {
    sprite.mutate([&](auto w, auto h, auto rbuf, auto gbuf, auto bbuf) {
        const size_t size = w * h;
        __m128i clrr = _mm_set1_epi8(static_cast<int8_t>(r));
        __m128i clrg = _mm_set1_epi8(static_cast<int8_t>(g));
        __m128i clrb = _mm_set1_epi8(static_cast<int8_t>(b));

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

void draw_back_on_device() {
    sprite.blit_on_frame_buffer(frame_buffer, 0, 0);
    frame_buffer.blit_on_dc(h_dc);
}
