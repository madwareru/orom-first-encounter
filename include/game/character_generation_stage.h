#ifndef CHARACHTER_GENERATION_STAGE_H__
#define CHARACHTER_GENERATION_STAGE_H__

#include <memory>
#include <cstdint>
#include <random>

struct ResourceFile;
struct SOASpriteRGB;
struct Sprite16a;

namespace Game {
    struct MouseState;
    namespace CharacterGenerationStage {
        struct Stage {
            Stage(std::shared_ptr<ResourceFile> main_resources, uint16_t window_width, uint16_t window_height);
            void on_enter();
            void update(const MouseState& mouse_state);
            void render(SOASpriteRGB &background_sprite);
        private:
            void handle_button_click(uint8_t button_id);
            void draw_sprinkle(SOASpriteRGB& background_sprite);
            uint8_t get_some_random();

            bool mouse_down_;

            std::shared_ptr<ResourceFile> graphic_resources_;

            std::shared_ptr<SOASpriteRGB> menu_background_;
            std::shared_ptr<SOASpriteRGB> menu_mask_;
            uint16_t menu_left_;
            uint16_t menu_right_;
            uint16_t menu_top_;
            uint16_t menu_bottom_;

            uint8_t last_menu_selection_;
            uint8_t current_button_order_;
            bool last_frame_lmb_down_;

            uint8_t selected_hero_;
            uint8_t selected_difficulty_;

            uint16_t star_frame_;
            uint8_t star_anim_ticks_remain_{0};
            uint16_t star_x_{0};
            uint16_t star_y_{0};

            std::shared_ptr<Sprite16a> blind_sprite_;
            std::shared_ptr<SOASpriteRGB> ok_button_sprite_;
            std::shared_ptr<SOASpriteRGB> amulet_button_sprite_;
            std::shared_ptr<SOASpriteRGB> hero_button_sprites_[4][3];
            std::shared_ptr<SOASpriteRGB> difficulty_button_sprites_[3][3];
        };
    }
}

#endif /* end of include guard: CHARACHTER_GENERATION_STAGE_H__ */
