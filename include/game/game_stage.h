#ifndef GAME_STAGE_H
#define GAME_STAGE_H

#include <memory>
#include <cstdint>
#include <vector>

struct ResourceFile;
struct SOASpriteRGB;

namespace Game {
    struct MouseState;
    namespace GameStage {
        struct GameStageShared {
            uint8_t* terrain_tile_x_cache;
            uint8_t* terrain_tile_y_cache;
            uint8_t* terrain_tile_u_cache;
            uint8_t* terrain_tile_v_cache;
            uint16_t camera_x;
            uint16_t camera_y;
        };

        struct Stage {
            Stage(std::shared_ptr<ResourceFile> graphic_resources,
                std::shared_ptr<ResourceFile> scenario_resources,
                uint16_t window_width,
                uint16_t window_height);
            void on_enter();
            void update(const MouseState& mouse_state);
            void render(SOASpriteRGB &background_sprite);
            ~Stage();
        private:
            uint16_t window_width_;
            uint16_t window_height_;
            //void handle_button_click(uint8_t button_id);

            //bool mouse_down_;

            std::shared_ptr<ResourceFile> graphic_resources_;
            std::shared_ptr<ResourceFile> scenario_resources_;

            uint8_t* terrain_cache_;
            GameStageShared render_shared_;

            std::vector<std::shared_ptr<SOASpriteRGB>> tiles_[4]{
                std::vector<std::shared_ptr<SOASpriteRGB>>{},
                std::vector<std::shared_ptr<SOASpriteRGB>>{},
                std::vector<std::shared_ptr<SOASpriteRGB>>{},
                std::vector<std::shared_ptr<SOASpriteRGB>>{}
            };
        };
    }
}

#endif /* end of include guard: GAME_STAGE_H */
