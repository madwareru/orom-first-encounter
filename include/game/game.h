#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <vector>

#include <GLFW/glfw3.h>

#include <windowing/window.h>

#include <util/defer_action.h>
#include <util/macro_shared.h>

#include <graphics/soaspritergb.h>
#include <graphics/soaspritergba.h>
#include <graphics/Sprite16a.h>

#include <loaders/pngloader.h>
#include <loaders/resource_file.h>
#include <loaders/registry_file.h>

#include <game/cursor_state.h>
#include <game/systems/systems.h>
#include <game/components/components.h>

#include <ecs.hpp/ecs.hpp>

namespace Game {
    enum class event {
        start_new_game,
        close_game,
        goto_main_menu,
        start_adventure,
        set_cursor
    };

    struct CloseGameEvent{};

    struct MouseState {
        uint16_t mouse_x{0};
        uint16_t mouse_y{0};
        bool left_button_down{false};
        bool middle_button_down{false};
        bool right_button_down{false};
    };

    namespace CityStage {
        extern ecs_hpp::registry world;
        struct update_feature{};
        struct rendering_feature{};
    }

    namespace GameStage {
        extern ecs_hpp::registry world;

        // struct terrain_event{
        //     GameStageShared* shared_data;
        // };

        struct terrain_feature{};
        struct update_feature{};
        struct rendering_feature{};
    }

    extern GLFWwindow* glfw_window;
    extern uint16_t window_width;
    extern uint16_t window_height;
    extern bool windowed;

    extern uint8_t clear_r;
    extern uint8_t clear_g;
    extern uint8_t clear_b;

    void init();
    void update(double delta_time);
    void render(SOASpriteRGB& background_sprite);

    void dispatch_message(const event& message);
    void dispatch_message(const event& message, uint8_t param);
    void dispatch_message(const event& message, uint8_t param0, uint8_t param1);

    void key_callback(
        GLFWwindow* window,
        int key,
        int scancode,
        int action,
        int mods
    );

    void mouse_callback(
        GLFWwindow* window,
        double xpos,
        double ypos
    );

    void mouse_button_callback(
        GLFWwindow* window,
        int button,
        int action,
        int mods
    );
}

#endif // GAME_H
