#include <game/main_menu_stage.h>
#include <game/game.h>
#include <game/shared/shared_res.h>

#include <graphics/soaspritergb.h>
#include <loaders/resource_file.h>

#include <util/macro_shared.h>

#include <unordered_map>

const uint16_t OFF_GAME_SCREEN_WIDTH = 640;
const uint16_t OFF_GAME_SCREEN_HEIGHT = 480;

// BUTTON_NAME, ID, ORDER, LEFT, TOP
DELCARE_BUTTON(NEW_GAME_BUTTON,     128, 0, 112, 64)
DELCARE_BUTTON(NETWORK_GAME_BUTTON, 144, 1, 84,  88)
DELCARE_BUTTON(VIDEO_BUTTON,        160, 2, 84,  236)
DELCARE_BUTTON(AUTHORS_BUTTON,      176, 3, 112, 276)
DELCARE_BUTTON(OLD_GAME_BUTTON,     192, 4, 320, 60)
DELCARE_BUTTON(SERVER_BUTTON,       208, 5, 324, 88)
DELCARE_BUTTON(FAME_HALL_BUTTON,    224, 6, 324, 236)
DELCARE_BUTTON(EXIT_BUTTON,         240, 7, 324, 276)

const uint8_t NONE_BUTTON_ORDER = 8;

// It should match with order
const uint16_t BUTTON_COORDS[8][2] = {
    COORDS_OF(NEW_GAME_BUTTON),
    COORDS_OF(NETWORK_GAME_BUTTON),
    COORDS_OF(VIDEO_BUTTON),
    COORDS_OF(AUTHORS_BUTTON),
    COORDS_OF(OLD_GAME_BUTTON),
    COORDS_OF(SERVER_BUTTON),
    COORDS_OF(FAME_HALL_BUTTON),
    COORDS_OF(EXIT_BUTTON)
};

namespace Game {
    namespace MainMenuStage {
        Stage::Stage(uint16_t window_width,
                     uint16_t window_height
        ) :
            last_main_menu_selection {0},
            current_button_order{NONE_BUTTON_ORDER},
            last_frame_lmb_down{false}
        {
            auto[backgound_success, backgound_bmp] = Game::Resources::Main().read_bmp_shared("graphics/mainmenu/menu_.bmp");
            if(backgound_success) {
                main_menu_background = backgound_bmp;
            } else {
                throw std::runtime_error("couldn't load main menu graphics");
            }

            auto[mask_success, mask_bmp] = Game::Resources::Main().read_mask_shared("graphics/mainmenu/menumask.bmp");
            if(mask_success) {
                main_menu_mask = mask_bmp;
            } else {
                throw std::runtime_error("couldn't load main menu graphics");
            }

            for(uint16_t j = 1; j <= 8; ++j) {
                char buffer[40];
                size_t order = j-1;
                sprintf(buffer, "graphics/mainmenu/button%u.bmp", j);
                auto [hover_succ, hover_res] = Game::Resources::Main().read_bmp_shared(buffer);
                if(hover_succ) {
                    button_sprites[order][0] = hover_res;
                } else {
                    throw std::runtime_error("couldn't load main menu graphics");
                }

                sprintf(buffer, "graphics/mainmenu/button%up.bmp", j);
                auto [click_succ, click_res] = Game::Resources::Main().read_bmp_shared(buffer);
                if(click_succ) {
                    button_sprites[order][1] = click_res;
                } else {
                    throw std::runtime_error("couldn't load main menu graphics");
                }
            }

            main_menu_left = (window_width - OFF_GAME_SCREEN_WIDTH) / 2;
            main_menu_top = (window_height - OFF_GAME_SCREEN_HEIGHT) / 2;

            main_menu_right = main_menu_left + OFF_GAME_SCREEN_WIDTH;
            main_menu_bottom = main_menu_top + OFF_GAME_SCREEN_HEIGHT;
        }

        void Stage::update(const MouseState& mouse_state) {
            if(mouse_state.mouse_x < main_menu_left || mouse_state.mouse_x >= main_menu_right) return;
            if(mouse_state.mouse_y < main_menu_top || mouse_state.mouse_y >= main_menu_bottom) return;
            auto selection_changed = false;
            auto pixel = main_menu_mask->get_mask_pixel(
                mouse_state.mouse_x - main_menu_left,
                mouse_state.mouse_y - main_menu_top
            );
            if(last_main_menu_selection != pixel) {
                last_main_menu_selection = pixel;
                selection_changed = true;
            }
            mouse_down_ = mouse_state.left_button_down;
            if(mouse_down_) {
                last_frame_lmb_down = true;
            } else {
                if(last_frame_lmb_down) {
                    handle_button_click(last_main_menu_selection);
                    last_frame_lmb_down = false;
                }
            }

            if(!selection_changed) return;

            switch (last_main_menu_selection) {
                LOOKUP_BUTTON_CASE(current_button_order, EXIT_BUTTON)
                LOOKUP_BUTTON_CASE(current_button_order, FAME_HALL_BUTTON)
                LOOKUP_BUTTON_CASE(current_button_order, SERVER_BUTTON)
                LOOKUP_BUTTON_CASE(current_button_order, OLD_GAME_BUTTON)
                LOOKUP_BUTTON_CASE(current_button_order, NEW_GAME_BUTTON)
                LOOKUP_BUTTON_CASE(current_button_order, NETWORK_GAME_BUTTON)
                LOOKUP_BUTTON_CASE(current_button_order, VIDEO_BUTTON)
                LOOKUP_BUTTON_CASE(current_button_order, AUTHORS_BUTTON)
                LOOKUP_CASE(current_button_order, 0, NONE_BUTTON_ORDER)
            }
        }

        void Stage::handle_button_click(uint8_t button_id) {
            switch (button_id) {
            case EXIT_BUTTON_ID:
                Game::dispatch_message(Game::event::close_game);
                break;
            case NEW_GAME_BUTTON_ID:
                Game::dispatch_message(Game::event::start_new_game);
                break;
            default:
                break;
            }
        }

        void Stage::on_enter() {
            last_main_menu_selection = 0;
            current_button_order = NONE_BUTTON_ORDER;
            last_frame_lmb_down = false;
        }

        void Stage::render(SOASpriteRGB &background_sprite) {
            main_menu_background->blit_on_sprite(background_sprite, main_menu_left, main_menu_top);

            if(current_button_order == NONE_BUTTON_ORDER) return;

            uint16_t coord_x = main_menu_left + GET_BUTTON_X(current_button_order);
            uint16_t coord_y = main_menu_top + GET_BUTTON_Y(current_button_order);
            if(mouse_down_) {
                switch (current_button_order) {
                    case EXIT_BUTTON_ORDER:
                        coord_x -= 4;
                        coord_y -= 4;
                        break;
                    case AUTHORS_BUTTON_ORDER:
                        coord_x += 4;
                        coord_y -= 4;
                        break;
                    case OLD_GAME_BUTTON_ORDER:
                        coord_y += 4;
                        break;
                    case VIDEO_BUTTON_ORDER:
                    case NETWORK_GAME_BUTTON_ORDER:
                    case NEW_GAME_BUTTON_ORDER:
                        coord_x += 4;
                        break;
                }
            }
            uint8_t mouse_state = (mouse_down_) ? 1 : 0;
            button_sprites[current_button_order][mouse_state]->blit_on_sprite(background_sprite, coord_x, coord_y);
        }
    }
}
