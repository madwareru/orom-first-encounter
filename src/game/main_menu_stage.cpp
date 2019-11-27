#include <game/main_menu_stage.h>

#include <graphics/soaspritergb.h>
#include <loaders/resource_file.h>

namespace Game {
    namespace MainMenuStage {
        Stage::Stage(std::shared_ptr<ResourceFile> main_resources,
                     uint16_t window_width,
                     uint16_t window_height
        ) : main_resources_{main_resources} {
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

        void Stage::update(double delta_time, uint32_t mouse_x, uint32_t mouse_y, bool mouse_down) {
            if(mouse_x < main_menu_left || mouse_x >= main_menu_right) return;
            if(mouse_y < main_menu_top || mouse_y >= main_menu_bottom) return;
            auto selection_changed = false;
            main_menu_mask->mutate([&](auto w, auto h, auto b, auto g, auto r){
                auto pixel = r[w * (mouse_y - main_menu_top) + mouse_x - main_menu_left];
                if(last_main_menu_selection != pixel) {
                    last_main_menu_selection = pixel;
                    selection_changed = true;
                }
            });
            mouse_down_ = mouse_down;
            if(selection_changed) {
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
        }

        void Stage::on_enter() {
            last_main_menu_selection = 0;
            current_button_order = NONE_BUTTON_ORDER;
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
