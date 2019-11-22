#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <memory>
#include <emmintrin.h>

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <graphics/framebuffer.h>
#include <graphics/soaspritergb.h>

typedef void (*render_proc)(SOASpriteRGB& back_buffer);
typedef void (*update_proc)(double delta_time);
typedef void (*init_proc)(void);

struct WindowCreationParams {
    const char* window_name;
    uint16_t w_width;
    uint16_t w_height;
    bool fullscreen;

    uint8_t clear_color_r;
    uint8_t clear_color_g;
    uint8_t clear_color_b;
};

#define INIT_WINDOW(window_params)    \
    glfwCreateWindow(                 \
        window_params.w_width,        \
        window_params.w_height,       \
        window_params.window_name,    \
        window_params.fullscreen      \
            ? glfwGetPrimaryMonitor() \
            : nullptr,                \
        nullptr                       \
    )

bool start_main_loop(
    GLFWwindow* glfw_window,
    const WindowCreationParams& window_params,
    init_proc   init_proc_addr,
    update_proc update_proc_addr,
    render_proc render_proc_addr);

#endif // WINDOW_H