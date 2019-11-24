#include <game/game.h>

void Game::init() {
    graphic_resources = std::make_shared<ResourceFile>("graphics.res");
    graphic_resources->with_registry_resource(
        "units/units.reg",
        [](auto units_reg_file) {
            LOG("registry succesfully loaded from resource");
            auto [files_found, files_value] = units_reg_file->get_string("Files/File0");
            if(files_found) {
                LOG("Found Files/File0 entry of type string with a value of \"" << files_value << "\"");
            }
        },
        []() {
            LOG_ERROR("this is not a registry resource");
        }
    );

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

void Game::update(double delta_time) {

}

void Game::render(SOASpriteRGB &background_sprite) {
    size_t x = 0;
    size_t y = 0;
    for(auto tileset : tiles) {
        for(auto tile : tileset) {
            tile->blit_on_sprite(background_sprite, x, y);
            x += 32;
            if(x >= 1024) {
                x %= 1024;
                y += 32 * 14;
            }
        }
    }
}
