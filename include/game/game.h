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
        std::vector<std::shared_ptr<SOASpriteRGB>> tiles[4];
    }

    void init();
    void update(double delta_time);
    void render(SOASpriteRGB& background_sprite);
}

#endif // GAME_H
