#include <game/main_menu_stage.h>
#include <game/game.h>

#include <graphics/soaspritergb.h>
#include <loaders/resource_file.h>

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

namespace Game {
    namespace MainMenuStage {
        Stage::Stage(std::shared_ptr<ResourceFile> main_resources,
                     uint16_t window_width,
                     uint16_t window_height
        ) :
            main_resources_{main_resources},
            last_main_menu_selection {0},
            current_button_order{NONE_BUTTON_ORDER},
            last_frame_lmb_down{false}
        {
            auto[backgound_success, backgound_bmp] = main_resources->read_bmp_shared("graphics/mainmenu/menu_.bmp");
            if(backgound_success) {
                main_menu_background = backgound_bmp;
            } else {
                throw std::runtime_error("couldn't load main menu graphics");
            }

            auto[mask_success, mask_bmp] = main_resources->read_mask_shared("graphics/mainmenu/menumask.bmp");
            if(mask_success) {
                main_menu_mask = mask_bmp;
            } else {
                throw std::runtime_error("couldn't load main menu graphics");
            }

            for(uint16_t j = 1; j <= 8; ++j) {
                char buffer[40];
                size_t order = j-1;
                sprintf(buffer, "graphics/mainmenu/button%u.bmp", j);
                auto [hover_succ, hover_res] = main_resources->read_bmp_shared(buffer);
                if(hover_succ) {
                    button_sprites[order][0] = hover_res;
                } else {
                    throw std::runtime_error("couldn't load main menu graphics");
                }

                sprintf(buffer, "graphics/mainmenu/button%up.bmp", j);
                auto [click_succ, click_res] = main_resources->read_bmp_shared(buffer);
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

        void Stage::update(double deltatime, const MouseState& mouse_state) {
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
                case EXIT_BUTTON_ID:
                    current_button_order = EXIT_BUTTON_ORDER;
                    break;
                case FAME_HALL_BUTTON_ID:
                    current_button_order = FAME_HALL_BUTTON_ORDER;
                    break;
                case SERVER_BUTTON_ID:
                    current_button_order = SERVER_BUTTON_ORDER;
                    break;
                case OLD_GAME_BUTTON_ID:
                    current_button_order = OLD_GAME_BUTTON_ORDER;
                    break;
                case NEW_GAME_BUTTON_ID:
                    current_button_order = NEW_GAME_BUTTON_ORDER;
                    break;
                case NETWORK_GAME_BUTTON_ID:
                    current_button_order = NETWORK_GAME_BUTTON_ORDER;
                    break;
                case VIDEO_BUTTON_ID:
                    current_button_order = VIDEO_BUTTON_ORDER;
                    break;
                case AUTHORS_BUTTON_ID:
                    current_button_order = AUTHORS_BUTTON_ORDER;
                    break;
                case 0:
                    current_button_order = NONE_BUTTON_ORDER;
                    break;
            }
        }

        void Stage::handle_button_click(uint8_t button_id) {
            switch (button_id) {
            case EXIT_BUTTON_ID:
                Game::initiate_game_closing();
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

            if(current_button_order >= NONE_BUTTON_ORDER) return;

            auto coord_x = main_menu_left + BUTTON_COORDS[current_button_order][0];
            auto coord_y = main_menu_top + BUTTON_COORDS[current_button_order][1];
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
