#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <emmintrin.h>
#include <vector>

#include <GLFW/glfw3.h>

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

#include <game/systems/systems.h>
#include <game/components/components.h>

#ifdef max
    #undef max
    #undef min
    #define max_min_undef
#endif
#include <ecs.hpp/ecs.hpp>

namespace Game {
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

    namespace MainMenuStage {
        extern ecs_hpp::registry world;
        struct update_feature;
        struct rendering_feature;
    }

    namespace CityStage {
        extern ecs_hpp::registry world;
        struct update_feature;
        struct rendering_feature;
    }

    namespace GameStage {
        extern ecs_hpp::registry world;
        extern uint8_t* terrain_cache;
        extern uint8_t* terrain_tile_x_cache;
        extern uint8_t* terrain_tile_y_cache;
        extern uint8_t* terrain_tile_u_cache;
        extern uint8_t* terrain_tile_v_cache;

        struct terrain_feature;
        struct update_feature;
        struct rendering_feature;
    }

    extern GLFWwindow* glfw_window;
    extern uint16_t window_width;
    extern uint16_t window_height;
    extern bool windowed;

    void init();
    void update(double delta_time);
    void render(SOASpriteRGB& background_sprite);

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

