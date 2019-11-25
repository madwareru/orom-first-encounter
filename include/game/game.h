#ifndef GAME_H
#define GAME_H

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

namespace Game {
    namespace  {
        std::shared_ptr<ResourceFile> graphic_resources;
        std::vector<std::shared_ptr<SOASpriteRGB>> tiles[4] = {
            std::vector<std::shared_ptr<SOASpriteRGB>>{},
            std::vector<std::shared_ptr<SOASpriteRGB>>{},
            std::vector<std::shared_ptr<SOASpriteRGB>>{},
            std::vector<std::shared_ptr<SOASpriteRGB>>{}
        };
    }

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

