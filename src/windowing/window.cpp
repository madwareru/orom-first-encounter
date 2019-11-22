#include <windowing/window.h>
#include <util/macro_shared.h>

#define FPS_60_MILLIS 0.0166
//#define VSYNC_ON

bool start_window(GLFWwindow* glfw_window, const WindowCreationParams& window_params) {
    HWND h_window;
    HDC h_dc;
    char title_buf[255];
    FrameBuffer frame_buffer{window_params.w_width, window_params.w_height};

    auto clear_r = window_params.clear_color_r;
    auto clear_g = window_params.clear_color_g;
    auto clear_b = window_params.clear_color_b;

    auto render = (window_params.render_proc_addr);
    auto update = (window_params.update_proc_addr);
    auto init   = (window_params.init_proc_addr);

    h_window = glfwGetWin32Window(glfw_window);
    h_dc = GetDC(h_window);

    //glfwSetKeyCallback(glfw_window, &key_callback);
    //glfwSetCursorPosCallback(glfw_window, &cursor_position_callback);
    //glfwSetMouseButtonCallback(glfw_window, &mouse_button_callback);
    //glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    //glfwSetWindowIcon(glfw_window, 1, &icon_image);

    double prev_time = glfwGetTime();
    double last_frame_gtime = glfwGetTime();
    int32_t fps = 0;

    LOG("CREATING A BACKGROUNG SPRITE WITH W = " << window_params.w_width << ", H = " << window_params.w_height);
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
        // clear
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
