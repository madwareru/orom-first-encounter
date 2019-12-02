#include <iostream>
#include <fstream>
#include <memory>
#include <emmintrin.h>
#include <graphics/soaspritergb.h>
#include <graphics/framebuffer.h>
#include <windowing/window.h>

#include <util/macro_shared.h>
#include <util/defer_action.h>

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#define FPS_60_MILLIS 0.014
#define VSYNC_ON

LifetimeProcHolder::LifetimeProcHolder(
    init_proc   init_proc_addr_p,
    update_proc update_proc_addr_p,
    render_proc render_proc_addr_p
) :
    init_proc_addr{init_proc_addr_p},
    update_proc_addr{update_proc_addr_p},
    render_proc_addr{render_proc_addr_p}
{}

bool start_main_loop(
    GLFWwindow* glfw_window,
    const WindowCreationParams& window_params,
    const LifetimeProcHolder& lifetime_procs,
    const std::vector<
       std::variant<
            KeyCallbackHolder,
            CursorPosCallbackHolder,
            MouseButtonCallbackHolder>
        >& eventCallbacks
) {
    HWND h_window;
    HDC h_dc;
    char title_buf[255];
    FrameBuffer frame_buffer{window_params.w_width, window_params.w_height};

    auto render = lifetime_procs.render_proc_addr;
    auto update = lifetime_procs.update_proc_addr;
    auto init   = lifetime_procs.init_proc_addr;

    glfwSetWindowSizeLimits(
        glfw_window,
        window_params.w_width,
        window_params.w_height,
        window_params.w_width,
        window_params.w_height
    );

    h_window = glfwGetWin32Window(glfw_window);
    h_dc = GetDC(h_window);

    for(auto callback : eventCallbacks) {
        std::visit([&](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            #define IF_MATCH(x) if constexpr (std::is_same_v<T, x>)
            #define EL_IF_MATCH(x) else IF_MATCH(x)

            IF_MATCH(KeyCallbackHolder) glfwSetKeyCallback(glfw_window, arg.fun);
            EL_IF_MATCH(CursorPosCallbackHolder) glfwSetCursorPosCallback(glfw_window, arg.fun);
            EL_IF_MATCH(MouseButtonCallbackHolder) glfwSetMouseButtonCallback(glfw_window, arg.fun);
            #undef EL_IF_MATCH
            #undef IF_MATCH
        },
        callback);
    }

    glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    //glfwSetWindowIcon(glfw_window, 1, &icon_image);

    double prev_time = glfwGetTime();
    double last_frame_gtime = glfwGetTime();
    int32_t fps = 0;

    SOASpriteRGB background_sprite{window_params.w_width, window_params.w_height};

    (*init)();

    while(!glfwWindowShouldClose(glfw_window)) {
        double global_time = glfwGetTime();
        double delta_time = global_time - last_frame_gtime;
        if(global_time - prev_time >= 1.0) {
            sprintf(title_buf, "%s %d fps", window_params.window_name, fps);
            glfwSetWindowTitle(glfw_window, title_buf);
            fps = 0;
            prev_time = global_time;
        } else {
            ++fps;
        }

#ifdef VSYNC_ON
        double point_a = glfwGetTime();
#endif
        (*update)(delta_time);
        (*render)(background_sprite);

        background_sprite.blit_on_frame_buffer(frame_buffer, 0, 0);
        frame_buffer.blit_on_dc(h_dc);
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

    return true;
}
