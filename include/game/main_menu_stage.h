#ifndef MAIN_MENU_STAGE_H_
#define MAIN_MENU_STAGE_H_

#include <memory>
#include <cstdint>

struct ResourceFile;
struct SOASpriteRGB;

namespace Game {

    struct MouseState;

    namespace MainMenuStage {
        struct Stage {
            Stage(std::shared_ptr<ResourceFile> main_resources, uint16_t window_width, uint16_t window_height);
            void on_enter();
            void update(const MouseState& mouse_state);
            void render(SOASpriteRGB &background_sprite);
        private:
            void handle_button_click(uint8_t button_id);

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
            bool last_frame_lmb_down;

            std::shared_ptr<SOASpriteRGB> button_sprites[8][2];
        };
    }
}

#endif /* end of include guard: MAIN_MENU_STAGE_H_ */
