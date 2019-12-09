#include <game/character_generation_stage.h>
#include <game/game.h>
#include <game/shared/shared_res.h>

#include <graphics/soaspritergb.h>
#include <loaders/resource_file.h>

#include <util/macro_shared.h>

#include <unordered_map>
#include <ctime>

const uint16_t OFF_GAME_SCREEN_WIDTH = 640;
const uint16_t OFF_GAME_SCREEN_HEIGHT = 480;

// BUTTON_NAME, ID, ORDER, LEFT, TOP
DELCARE_BUTTON(DIFFICULTY_EASY_BUTTON,   20, 0, 60, 196)
DELCARE_BUTTON(DIFFICULTY_MEDIUM_BUTTON, 40, 1, 0, 110)
DELCARE_BUTTON(DIFFICULTY_HARD_BUTTON,   60, 2, 48, 65)

DELCARE_BUTTON(HERO_DANAS_BUTTON,        80,  3, 16, 273)
DELCARE_BUTTON(HERO_NAIRA_BUTTON,        100, 4, 124, 166)
DELCARE_BUTTON(HERO_RENIESTA_BUTTON,     120, 5, 288, 130)
DELCARE_BUTTON(HERO_FERGARD_BUTTON,      140, 6, 416, 190)

DELCARE_BUTTON(AMULET_BUTTON,            160, 7, 528, 140)
DELCARE_BUTTON(OKAY_BUTTON,              180, 8, 468, 373)

const uint8_t NONE_BUTTON_ORDER = 9;

// It should match with order
const uint16_t BUTTON_COORDS[9][2] = {
    COORDS_OF(DIFFICULTY_EASY_BUTTON),
    COORDS_OF(DIFFICULTY_MEDIUM_BUTTON),
    COORDS_OF(DIFFICULTY_HARD_BUTTON),
    COORDS_OF(HERO_DANAS_BUTTON),
    COORDS_OF(HERO_NAIRA_BUTTON),
    COORDS_OF(HERO_RENIESTA_BUTTON),
    COORDS_OF(HERO_FERGARD_BUTTON),
    COORDS_OF(AMULET_BUTTON),
    COORDS_OF(OKAY_BUTTON)
};

const uint16_t SPRINKLE_COORDS[39][2] = {
    COORDS_OF_OFFSETTED(DIFFICULTY_EASY_BUTTON, 38, 63),
    COORDS_OF_OFFSETTED(DIFFICULTY_EASY_BUTTON, 11, 12),
    COORDS_OF_OFFSETTED(DIFFICULTY_EASY_BUTTON, 0, 42),
    COORDS_OF_OFFSETTED(DIFFICULTY_MEDIUM_BUTTON, 38, 63),
    COORDS_OF_OFFSETTED(DIFFICULTY_MEDIUM_BUTTON, 11, 12),
    COORDS_OF_OFFSETTED(DIFFICULTY_MEDIUM_BUTTON, 0, 42),
    COORDS_OF_OFFSETTED(DIFFICULTY_HARD_BUTTON, 38, 63),
    COORDS_OF_OFFSETTED(DIFFICULTY_HARD_BUTTON, 11, 12),
    COORDS_OF_OFFSETTED(DIFFICULTY_HARD_BUTTON, 0, 42),
    COORDS_OF_OFFSETTED(HERO_DANAS_BUTTON, 38, 63),
    COORDS_OF_OFFSETTED(HERO_DANAS_BUTTON, 11, 12),
    COORDS_OF_OFFSETTED(HERO_DANAS_BUTTON, 0, 42),
    COORDS_OF_OFFSETTED(HERO_NAIRA_BUTTON, 38, 63),
    COORDS_OF_OFFSETTED(HERO_NAIRA_BUTTON, 11, 12),
    COORDS_OF_OFFSETTED(HERO_NAIRA_BUTTON, 0, 42),
    COORDS_OF_OFFSETTED(HERO_RENIESTA_BUTTON, 38, 63),
    COORDS_OF_OFFSETTED(HERO_RENIESTA_BUTTON, 11, 12),
    COORDS_OF_OFFSETTED(HERO_RENIESTA_BUTTON, 0, 42),
    COORDS_OF_OFFSETTED(HERO_FERGARD_BUTTON, 38, 63),
    COORDS_OF_OFFSETTED(HERO_FERGARD_BUTTON, 11, 12),
    COORDS_OF_OFFSETTED(HERO_FERGARD_BUTTON, 0, 42),
    COORDS_OF_OFFSETTED(AMULET_BUTTON, 38, 63),
    COORDS_OF_OFFSETTED(AMULET_BUTTON, 11, 12),
    COORDS_OF_OFFSETTED(AMULET_BUTTON, 0, 42),
    COORDS_OF_OFFSETTED(OKAY_BUTTON, 38, 63),
    COORDS_OF_OFFSETTED(OKAY_BUTTON, 11, 12),
    COORDS_OF_OFFSETTED(OKAY_BUTTON, 0, 42),
    COORDS_OF_OFFSETTED(OKAY_BUTTON, 38, 63),
    COORDS_OF_OFFSETTED(OKAY_BUTTON, 11, 12),
    COORDS_OF_OFFSETTED(OKAY_BUTTON, 0, 42),
    COORDS_OF_OFFSETTED(OKAY_BUTTON, 38, 63),
    COORDS_OF_OFFSETTED(OKAY_BUTTON, 11, 12),
    COORDS_OF_OFFSETTED(OKAY_BUTTON, 0, 42),
    COORDS_OF_OFFSETTED(OKAY_BUTTON, 38, 63),
    COORDS_OF_OFFSETTED(OKAY_BUTTON, 11, 12),
    COORDS_OF_OFFSETTED(OKAY_BUTTON, 0, 42),
    COORDS_OF_OFFSETTED(OKAY_BUTTON, 38, 63),
    COORDS_OF_OFFSETTED(OKAY_BUTTON, 11, 12),
    COORDS_OF_OFFSETTED(OKAY_BUTTON, 0, 42)
};

const uint8_t HOVER = 0;
const uint8_t HOVER_SELECTED = 1;
const uint8_t SELECTED = 2;

const uint8_t STAR_ANIM_TICKS = 2;

const char* hero_prefix[4] = {"mf", "ff", "fm", "mm"};

namespace Game {
    namespace CharacterGenerationStage {
        Stage::Stage(uint16_t window_width,
                     uint16_t window_height
        ) :
            last_menu_selection_ {0},
            current_button_order_{NONE_BUTTON_ORDER},
            last_frame_lmb_down_{false},
            selected_hero_{0},
            selected_difficulty_{0}
        {
            std::srand(std::time(nullptr));

            auto[backgound_success, backgound_bmp] = Game::Resources::Graphics().read_bmp_shared("interface/chrgen/precreate/mainarea.bmp");
            if(backgound_success) {
                menu_background_ = backgound_bmp;
            } else {
                throw std::runtime_error("couldn't load character creation menu graphics");
            }

            auto[mask_success, mask_bmp] = Game::Resources::Graphics().read_mask_shared("interface/chrgen/precreate/mask.bmp");
            if(mask_success) {
                menu_mask_ = mask_bmp;
            } else {
                throw std::runtime_error("couldn't load character creation menu graphics");
            }

            char buffer[256];

            for(uint16_t i = 0; i < 4; ++i) {
                sprintf(buffer, "interface/chrgen/precreate/heroes/%sl.bmp", hero_prefix[i]);
                auto [hover_succ, hover_res] = Game::Resources::Graphics().read_bmp_shared(buffer);
                if(hover_succ) {
                    hero_button_sprites_[i][0] = hover_res;
                } else {
                    throw std::runtime_error("couldn't load character creation menu graphics");
                }

                sprintf(buffer, "interface/chrgen/precreate/heroes/%slon.bmp", hero_prefix[i]);
                auto [click_succ, click_res] = Game::Resources::Graphics().read_bmp_shared(buffer);
                if(click_succ) {
                    hero_button_sprites_[i][1] = click_res;
                } else {
                    throw std::runtime_error("couldn't load character creation menu graphics");
                }

                sprintf(buffer, "interface/chrgen/precreate/heroes/%son.bmp", hero_prefix[i]);
                auto [selected_succ, selected_res] = Game::Resources::Graphics().read_bmp_shared(buffer);
                if(selected_succ) {
                    hero_button_sprites_[i][2] = selected_res;
                } else {
                    throw std::runtime_error("couldn't load character creation menu graphics");
                }
            }

            for(uint16_t i = 0; i < 3; ++i) {
                sprintf(buffer, "interface/chrgen/precreate/levels/level%ul.bmp", i);
                auto [hover_succ, hover_res] = Game::Resources::Graphics().read_bmp_shared(buffer);
                if(hover_succ) {
                    difficulty_button_sprites_[i][0] = hover_res;
                } else {
                    throw std::runtime_error("couldn't load character creation menu graphics");
                }

                sprintf(buffer, "interface/chrgen/precreate/levels/level%ulon.bmp", i);
                auto [click_succ, click_res] = Game::Resources::Graphics().read_bmp_shared(buffer);
                if(click_succ) {
                    difficulty_button_sprites_[i][1] = click_res;
                } else {
                    throw std::runtime_error("couldn't load character creation menu graphics");
                }

                sprintf(buffer, "interface/chrgen/precreate/levels/level%uon.bmp", i);
                auto [selected_succ, selected_res] = Game::Resources::Graphics().read_bmp_shared(buffer);
                if(selected_succ) {
                    difficulty_button_sprites_[i][2] = selected_res;
                } else {
                    throw std::runtime_error("couldn't load character creation menu graphics");
                }
            }

            auto [ok_succ, ok_res] = Game::Resources::Graphics().read_bmp_shared("interface/chrgen/precreate/buttonok.bmp");
            if(ok_succ) {
                ok_button_sprite_ = ok_res;
            } else {
                throw std::runtime_error("couldn't load character creation menu graphics");
            }

            auto [amulet_succ, amulet_res] = Game::Resources::Graphics().read_bmp_shared("interface/chrgen/precreate/amulet.bmp");
            if(amulet_succ) {
                amulet_button_sprite_ = amulet_res;
            } else {
                throw std::runtime_error("couldn't load character creation menu graphics");
            }

            auto [blind_succ, blind_res] = Game::Resources::Graphics().read_16a_shared("interface/chrgen/precreate/blind/sprites.16a");
            if(blind_succ) {
                blind_sprite_ = blind_res;
            } else {
                throw std::runtime_error("couldn't load character creation menu graphics");
            }

            menu_left_ = (window_width - OFF_GAME_SCREEN_WIDTH) / 2;
            menu_top_ = (window_height - OFF_GAME_SCREEN_HEIGHT) / 2;

            menu_right_ = menu_left_ + OFF_GAME_SCREEN_WIDTH;
            menu_bottom_ = menu_top_ + OFF_GAME_SCREEN_HEIGHT;
        }

        uint8_t Stage::get_some_random(){
            return rand() & 0xFF;
        }

        void Stage::update(const MouseState& mouse_state) {
            star_anim_ticks_remain_--;
            if(!star_anim_ticks_remain_) {
                star_frame_++;

                if(star_frame_ > blind_sprite_->frame_count() * 2) {
                    star_frame_ = 0;

                    auto new_star_pos_id = get_some_random() % 39;

                    star_x_ = SPRINKLE_COORDS[new_star_pos_id][0];
                    star_y_ = SPRINKLE_COORDS[new_star_pos_id][1];
                }
                star_anim_ticks_remain_ = STAR_ANIM_TICKS;
            }

            if(mouse_state.mouse_x < menu_left_ || mouse_state.mouse_x >= menu_right_) return;
            if(mouse_state.mouse_y < menu_top_ || mouse_state.mouse_y >= menu_bottom_) return;
            auto selection_changed = false;
            auto pixel = menu_mask_->get_mask_pixel(
                mouse_state.mouse_x - menu_left_,
                mouse_state.mouse_y - menu_top_
            );
            if(last_menu_selection_ != pixel) {
                last_menu_selection_ = pixel;
                selection_changed = true;
            }
            mouse_down_ = mouse_state.left_button_down;
            if(mouse_down_) {
                last_frame_lmb_down_ = true;
            } else {
                if(last_frame_lmb_down_) {
                    handle_button_click(last_menu_selection_);
                    last_frame_lmb_down_ = false;
                }
            }

            if(!selection_changed) return;

            switch (last_menu_selection_) {
                LOOKUP_BUTTON_CASE(current_button_order_, DIFFICULTY_EASY_BUTTON)
                LOOKUP_BUTTON_CASE(current_button_order_, DIFFICULTY_MEDIUM_BUTTON)
                LOOKUP_BUTTON_CASE(current_button_order_, DIFFICULTY_HARD_BUTTON)
                LOOKUP_BUTTON_CASE(current_button_order_, HERO_DANAS_BUTTON)
                LOOKUP_BUTTON_CASE(current_button_order_, HERO_NAIRA_BUTTON)
                LOOKUP_BUTTON_CASE(current_button_order_, HERO_FERGARD_BUTTON)
                LOOKUP_BUTTON_CASE(current_button_order_, HERO_RENIESTA_BUTTON)
                LOOKUP_BUTTON_CASE(current_button_order_, AMULET_BUTTON)
                LOOKUP_BUTTON_CASE(current_button_order_, OKAY_BUTTON)
                LOOKUP_CASE(current_button_order_, 0, NONE_BUTTON_ORDER)
            }
        }

        void Stage::handle_button_click(uint8_t button_id) {
            switch (button_id) {
            case AMULET_BUTTON_ID:
                Game::dispatch_message(Game::event::goto_main_menu);
                break;
            case HERO_DANAS_BUTTON_ID:
            case HERO_NAIRA_BUTTON_ID:
            case HERO_FERGARD_BUTTON_ID:
            case HERO_RENIESTA_BUTTON_ID:
                selected_hero_ = (button_id - HERO_DANAS_BUTTON_ID) / 20;
                break;
            case DIFFICULTY_EASY_BUTTON_ID:
            case DIFFICULTY_MEDIUM_BUTTON_ID:
            case DIFFICULTY_HARD_BUTTON_ID:
                selected_difficulty_ = (button_id - DIFFICULTY_EASY_BUTTON_ID) / 20;
                break;
            case OKAY_BUTTON_ID:
                Game::dispatch_message(Game::event::start_adventure, selected_hero_, selected_difficulty_);
                break;
            default:
                break;
            }
        }

        void Stage::on_enter() {
            last_menu_selection_ = 0;
            current_button_order_ = NONE_BUTTON_ORDER;
            last_frame_lmb_down_ = false;

            star_anim_ticks_remain_ = STAR_ANIM_TICKS;
            star_frame_ = 0;
            auto new_star_pos_id = get_some_random() % 39;

            star_x_ = SPRINKLE_COORDS[new_star_pos_id][0];
            star_y_ = SPRINKLE_COORDS[new_star_pos_id][1];
        }

        void Stage::draw_sprinkle(SOASpriteRGB& background_sprite) {
            if(star_frame_ >= blind_sprite_->frame_count()) return;
            blind_sprite_->blit_on_sprite(background_sprite, menu_left_ + star_x_, menu_top_ + star_y_, star_frame_);
        }

        void Stage::render(SOASpriteRGB &background_sprite) {
            menu_background_->blit_on_sprite(background_sprite, menu_left_, menu_top_);

            uint16_t coord_x;
            uint16_t coord_y;

            uint16_t selected_hero_order = selected_hero_ + HERO_DANAS_BUTTON_ORDER;
            uint16_t selected_difficulty_order = selected_difficulty_ + DIFFICULTY_EASY_BUTTON_ORDER;

            uint8_t kind = (current_button_order_ != selected_difficulty_order) ? SELECTED : HOVER_SELECTED;

            coord_x = menu_left_ + GET_BUTTON_X(selected_difficulty_order);
            coord_y = menu_top_ + GET_BUTTON_Y(selected_difficulty_order);

            difficulty_button_sprites_[selected_difficulty_][kind]->blit_on_sprite_colorkeyed16(
                background_sprite,
                coord_x,
                coord_y,
                0x00, 0x00, 0x00
            );

            kind = (current_button_order_ != selected_hero_order) ? SELECTED : HOVER_SELECTED;

            coord_x = menu_left_ + GET_BUTTON_X(selected_hero_order);
            coord_y = menu_top_ + GET_BUTTON_Y(selected_hero_order);

            hero_button_sprites_[selected_hero_][kind]->blit_on_sprite_colorkeyed16(
                background_sprite,
                coord_x,
                coord_y,
                0x00, 0x00, 0x00
            );


            if(current_button_order_ >= NONE_BUTTON_ORDER ||
               current_button_order_ == selected_hero_order  ||
               current_button_order_ == selected_difficulty_order){
                draw_sprinkle(background_sprite);
                return;
            }

            coord_x = menu_left_ + GET_BUTTON_X(current_button_order_);
            coord_y = menu_top_ + GET_BUTTON_Y(current_button_order_);

            if(current_button_order_ < HERO_DANAS_BUTTON_ORDER) {
                difficulty_button_sprites_[current_button_order_][HOVER]->blit_on_sprite_colorkeyed16(
                    background_sprite,
                    coord_x,
                    coord_y,
                    0x00, 0x00, 0x00
                );
            } else if(current_button_order_ < AMULET_BUTTON_ORDER) {
                hero_button_sprites_[current_button_order_ - HERO_DANAS_BUTTON_ORDER][HOVER]->blit_on_sprite_colorkeyed16(
                    background_sprite,
                    coord_x,
                    coord_y,
                    0x00, 0x00, 0x00
                );
            } else if(current_button_order_ == AMULET_BUTTON_ORDER) {
                amulet_button_sprite_->blit_on_sprite_colorkeyed16(
                    background_sprite,
                    coord_x,
                    coord_y,
                    0x00, 0x00, 0x00
                );
            } else if(current_button_order_ == OKAY_BUTTON_ORDER) {
                ok_button_sprite_->blit_on_sprite_colorkeyed16(
                    background_sprite,
                    coord_x,
                    coord_y,
                    0x00, 0x00, 0x00
                );
            }
            draw_sprinkle(background_sprite);
        }
    }
}
