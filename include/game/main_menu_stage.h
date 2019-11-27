#ifndef MAIN_MENU_STAGE_H__
#define MAIN_MENU_STAGE_H__

#include <memory>
#include <cstdint>

struct ResourceFile;
struct SOASpriteRGB;

namespace Game {
    namespace MainMenuStage {
        const uint16_t OFF_GAME_SCREEN_WIDTH = 640;
        const uint16_t OFF_GAME_SCREEN_HEIGHT = 480;

        const uint16_t EXIT_BUTTON_LEFT = 324;
        const uint16_t FAME_HALL_BUTTON_LEFT = 324;
        const uint16_t SERVER_BUTTON_LEFT = 324;
        const uint16_t OLD_GAME_BUTTON_LEFT = 320;
        const uint16_t NEW_GAME_BUTTON_LEFT = 112;
        const uint16_t NETWORK_GAME_BUTTON_LEFT = 84;
        const uint16_t VIDEO_BUTTON_LEFT = 84;
        const uint16_t AUTHORS_BUTTON_LEFT = 112;

        const uint16_t EXIT_BUTTON_TOP = 276;
        const uint16_t FAME_HALL_BUTTON_TOP = 236;
        const uint16_t SERVER_BUTTON_TOP = 88;
        const uint16_t OLD_GAME_BUTTON_TOP = 60;
        const uint16_t NEW_GAME_BUTTON_TOP = 64;
        const uint16_t NETWORK_GAME_BUTTON_TOP = 88;
        const uint16_t VIDEO_BUTTON_TOP = 236;
        const uint16_t AUTHORS_BUTTON_TOP = 276;

        const uint8_t EXIT_BUTTON_ID = 240;
        const uint8_t FAME_HALL_BUTTON_ID = 224;
        const uint8_t SERVER_BUTTON_ID = 208;
        const uint8_t OLD_GAME_BUTTON_ID = 192;
        const uint8_t NEW_GAME_BUTTON_ID = 128;
        const uint8_t NETWORK_GAME_BUTTON_ID = 144;
        const uint8_t VIDEO_BUTTON_ID = 160;
        const uint8_t AUTHORS_BUTTON_ID = 176;

        const uint8_t NEW_GAME_BUTTON_ORDER = 0;
        const uint8_t NETWORK_GAME_BUTTON_ORDER = 1;
        const uint8_t VIDEO_BUTTON_ORDER = 2;
        const uint8_t AUTHORS_BUTTON_ORDER = 3;
        const uint8_t OLD_GAME_BUTTON_ORDER = 4;
        const uint8_t SERVER_BUTTON_ORDER = 5;
        const uint8_t FAME_HALL_BUTTON_ORDER = 6;
        const uint8_t EXIT_BUTTON_ORDER = 7;
        const uint8_t NONE_BUTTON_ORDER = 8;

        const uint16_t BUTTON_COORDS[8][2] = {
            {NEW_GAME_BUTTON_LEFT, NEW_GAME_BUTTON_TOP},
            {NETWORK_GAME_BUTTON_LEFT, NETWORK_GAME_BUTTON_TOP},
            {VIDEO_BUTTON_LEFT, VIDEO_BUTTON_TOP},
            {AUTHORS_BUTTON_LEFT, AUTHORS_BUTTON_TOP},
            {OLD_GAME_BUTTON_LEFT, OLD_GAME_BUTTON_TOP},
            {SERVER_BUTTON_LEFT, SERVER_BUTTON_TOP},
            {FAME_HALL_BUTTON_LEFT, FAME_HALL_BUTTON_TOP},
            {EXIT_BUTTON_LEFT, EXIT_BUTTON_TOP}
        };

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

            uint8_t last_main_menu_selection{0};
            uint8_t current_button_order{NONE_BUTTON_ORDER};

            std::shared_ptr<SOASpriteRGB> button_sprites[8][2];
        };
    }
}

#endif /* end of include guard: MAIN_MENU_STAGE_H__ */
