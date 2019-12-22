#include <iostream>
#include <fstream>
#include <memory>
#include <emmintrin.h>
#include <graphics/soaspritergb.h>
#include <windowing/window.h>

#include <util/macro_shared.h>
#include <util/defer_action.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>

#define FPS_30_MILLIS 0.033
//#define VSYNC_ON

LifetimeProcHolder::LifetimeProcHolder(
    init_proc   init_proc_addr_p,
    update_proc update_proc_addr_p,
    render_proc render_proc_addr_p
) :
    init_proc_addr{init_proc_addr_p},
    update_proc_addr{update_proc_addr_p},
    render_proc_addr{render_proc_addr_p}
{}

namespace  {
    const char* vertex_shader =
        "#version 330 core\n"
        "layout (location = 0) in vec3 position;\n"
        "layout (location = 1) in vec2 uv;\n"
        "out vec2 uv_coords;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
        "    uv_coords = uv;\n;"
        "}";

    const char* fragment_shader =
        "#version 330 core\n"
        "in vec2 uv_coords;\n"
        "out vec4 color;\n"
        "uniform sampler2D main_texture;\n"
        "void main()\n"
        "{\n"
        "    color = texture(main_texture, uv_coords);\n"
        "}";
}

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
    glfwMakeContextCurrent(glfw_window);
    glfwMakeContextCurrent(glfw_window);

    glewExperimental = GL_FALSE;
    if (glewInit() != GLEW_OK)
    {
        LOG_ERROR("Failed to initialize GLEW");
        return false;
    }

    int width, height;
    glfwGetFramebufferSize(glfw_window, &width, &height);
    glViewport(0, 0, width, height);

    GLfloat vertices[] = {
        -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
         1.0f, -1.0f, 0.0f
    };

    GLfloat texCoords[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    GLuint vbo_vertices;
    glGenBuffers(1, &vbo_vertices);
    DEFER([&](){ glDeleteBuffers(1, &vbo_vertices); })
    GLuint vbo_uv;
    glGenBuffers(1, &vbo_uv);
    DEFER([&](){ glDeleteBuffers(1, &vbo_uv); })

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader, nullptr);
    glCompileShader(vertexShader);

    {
        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            LOG_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog);
        }
    }

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader, nullptr);
    glCompileShader(fragmentShader);

    {
        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            LOG_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog);
        }
    }

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    {
        GLint success;
        GLchar infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            LOG_ERROR("ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog);
        }
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    DEFER([&](){ glDeleteProgram(shaderProgram); })

    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    DEFER([&](){ glDeleteVertexArrays(1, &VAO); })

    GLuint texture;
    glGenTextures(1, &texture);
    DEFER([&](){ glDeleteTextures(1, &texture); })
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    char title_buf[255];

    auto fbw = window_params.w_width;
    auto fbh = window_params.w_height;

    GLuint PBO;
    glGenBuffers(1, &PBO);
    DEFER([&](){ glDeleteBuffers(1, &PBO); })
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, PBO);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, 3 * fbw * fbh, nullptr, GL_STREAM_DRAW);
    uint8_t* ptr = reinterpret_cast<uint8_t*>(glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY));
    if(ptr)
    {
        for(size_t s = fbw*fbh; s; --s) {
            *ptr++ = 0;
            *ptr++ = 0;
            *ptr++ = 0;
        }
        glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);  // release pointer to mapping buffer
    }
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        fbw, fbh,
        0,
        GL_BGR,
        GL_UNSIGNED_BYTE,
        nullptr
   );

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

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, PBO);
        glBufferData(GL_PIXEL_UNPACK_BUFFER, 3 * fbw * fbh, nullptr, GL_STREAM_DRAW);
        uint8_t* ptr = reinterpret_cast<uint8_t*>(glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY));
        if(ptr)
        {
            background_sprite.blit_on_opengl_buffer(ptr, fbw, fbh);
            glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);  // release pointer to mapping buffer
        }
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            fbw, fbh,
            0,
            GL_BGR,
            GL_UNSIGNED_BYTE,
            nullptr
       );
        glFinish();

        glClear(GL_COLOR);
        glUseProgram(shaderProgram);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
#ifdef VSYNC_ON
        if(delta_time > FPS_30_MILLIS + 0.0005) {
            glfwPollEvents();
        } else {
            double diff = point_a + FPS_30_MILLIS - glfwGetTime();
            while(diff > 0.0) {
                glfwWaitEventsTimeout(diff);
                diff = point_a + FPS_30_MILLIS - glfwGetTime();
            }
        }
#else
        glfwPollEvents();
#endif
        glfwSwapBuffers(glfw_window);
        last_frame_gtime = global_time;
    }

    return true;
}
