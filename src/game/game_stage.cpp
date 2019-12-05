#include <game/game_stage.h>

#include <loaders/resource_file.h>
#include <graphics/soaspritergb.h>

namespace Game {
    namespace GameStage {
        Stage::Stage(std::shared_ptr<ResourceFile> graphic_resources,
                     std::shared_ptr<ResourceFile> scenario_resources,
                     uint16_t window_width,
                     uint16_t window_height) :
                window_width_{window_width},
                window_height_{window_height},
                scenario_resources_{scenario_resources} {
            terrain_cache_ = new uint8_t[4 * window_width_ * window_height_];
            size_t offset = 0;

            render_shared_.terrain_tile_x_cache = &terrain_cache_[offset];
            offset += window_width * window_height;
            render_shared_.terrain_tile_y_cache = &terrain_cache_[offset];
            offset += window_width * window_height;
            render_shared_.terrain_tile_u_cache = &terrain_cache_[offset];
            offset += window_width * window_height;
            render_shared_.terrain_tile_v_cache = &terrain_cache_[offset];
            render_shared_.camera_x = 0;
            render_shared_.camera_y = 0;

            graphic_resources_ = graphic_resources;

            char buf[32];
            for(size_t i = 1; i <= 4; ++i) {
                const size_t capacity = (i < 4) ? 16 : 4;
                tiles_[i-1].reserve(capacity);
                for(size_t j = 0; j < capacity; ++j)
                {
                    if(j < 10) {
                        sprintf(buf, "terrain/tile%d-0%d.bmp", (int)i, (int)j);
                    } else {
                        sprintf(buf, "terrain/tile%d-%d.bmp", (int)i, (int)j);
                    }
                    auto[success, next_bmp] = graphic_resources_->read_bmp_shared(buf);
                    if(success) {
                        tiles_[i-1].emplace_back(next_bmp);
                    }
                }
            }
        }

        Stage::~Stage() {
            delete [] terrain_cache_;
        }

        void Stage::update(const MouseState &mouse_state) {

        }

        void Stage::render(SOASpriteRGB &background_sprite) {
            size_t x = 0;
            size_t y = 0;
            for(auto tileset : tiles_) {
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

        void Stage::on_enter() {

        }
    }
}
