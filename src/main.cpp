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
#include "pngloader.h"
#include <emmintrin.h>
#include "loaders/rage_of_mages_1_res.h"
#include "loaders/resource_file.h"

#define WIN_TITLE "Software rendering bootstrap"
#define WIN_W 1024
#define WIN_H 768
#define FPS_60_MILLIS 0.0166
#define FULLSCREEN false

//#define VSYNC_ON

namespace  {
    GLFWwindow* glfw_window;
    HWND h_window;
    HDC h_dc;
    char title_buf[255];
    FrameBuffer frame_buffer{WIN_W, WIN_H};
    SOASpriteRGB sprite{WIN_W, WIN_H};
    std::shared_ptr<ResourceFile> graphic_resources;
    std::shared_ptr<SOASpriteRGB> terrain_sprite_asset;
    std::shared_ptr<SOASpriteRGBA> transparent_sprite_asset;
    const size_t coord_range[32] = {
        33, 64, 973, 117, 45, 98, 128, 255,
        87, 17, 563, 343, 805, 488, 301, 505,
        451, 198, 828, 25, 323, 645, 739, 117,
        343, 805, 488, 301, 64, 973, 528, 215
    };

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
    terrain_sprite_asset = load_sprite_from_png<SOASpriteRGB>("superts2.png");
    transparent_sprite_asset = load_sprite_from_png<SOASpriteRGBA>("atlas.png");

    graphic_resources = std::make_shared<ResourceFile>("graphics.res");

    auto tile_4_03 = graphic_resources->get_resource("terrain/tile4-03.bmp");
    if(tile_4_03 != nullptr) {
        std::cout << "size of terrain/tile4-03.bmp in bytes are " << tile_4_03->bytes().size() << std::endl;
    }
}

void update(double delta_time) {

}

void render() {
    clear_back(0x40, 0x40, 0x40);
    terrain_sprite_asset->blit_on_sprite_colorkeyed16(sprite, 16, 16, 0xFF, 0, 0xFF);
    transparent_sprite_asset->blit_on_sprite(sprite, 64, 64);

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
