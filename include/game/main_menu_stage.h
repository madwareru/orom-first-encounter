#ifndef MAIN_MENU_STAGE_H__
#define MAIN_MENU_STAGE_H__

#include <memory>
#include <cstdint>

struct ResourceFile;
struct SOASpriteRGB;

namespace Game {
    namespace MainMenuStage {
        struct Stage {
            Stage(std::shared_ptr<ResourceFile> main_resources, uint16_t window_width, uint16_t window_height);
            void on_enter();
            void update(double deltatime, uint32_t mouse_x, uint32_t mouse_y, bool mouse_down);
            void render(SOASpriteRGB &background_sprite);
        private:
            bool mouse_down_;

            std::shared_ptr<ResourceFile> main_resources_;

            std::shared_ptr<SOASpriteRGB> main_menu_background;
            std::shared_ptr<SOASpriteRGB> main_menu_mask;
            uint16_t main_menu_left;
            uint16_t main_menu_right;
            uint16_t main_menu_top;
            uint16_t main_menu_bottom;

            uint8_t last_main_menu_selection;
            uint8_t current_button_order;

            std::shared_ptr<SOASpriteRGB> button_sprites[8][2];
        };
    }
}

#endif /* end of include guard: MAIN_MENU_STAGE_H__ */
