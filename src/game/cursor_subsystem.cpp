#include <game/cursor_subsystem.h>
#include <loaders/resource_file.h>
#include <graphics/soaspritergb.h>
#include <graphics/Sprite16a.h>
#include <game/game.h>
#include <util/macro_shared.h>

namespace Game {
    CursorSubsystem::CursorSubsystem(
            std::shared_ptr<ResourceFile> graphic_resources,
            Game::cursor_state initial_cursor) : current_frame_{0} {
        current_cursor_ = initial_cursor;
        size_t pos;

        #define LOAD_CURSOR(cursor_name, offset_x, offset_y)                            \
            pos = static_cast<size_t>(cursor_state::c_##cursor_name);                   \
            ofsset_x_array_[pos] = offset_x;                                            \
            ofsset_y_array_[pos] = offset_y;                                            \
            auto [cursor_name##_s, cursor_name##_r] =                                   \
            graphic_resources->read_16a_shared("cursors/" #cursor_name "/sprites.16a"); \
            if (cursor_name##_s) {                                                      \
                sprites_[pos] = cursor_name##_r;                                        \
            } else {                                                                    \
                throw std::runtime_error("fail on load cursor: " #cursor_name);         \
            }

        LOAD_CURSOR(arrow0, 0, 0)
        LOAD_CURSOR(arrow1, 0, 0)
        LOAD_CURSOR(arrow2, 0, 0)
        LOAD_CURSOR(arrow3, 0, 0)
        LOAD_CURSOR(arrow4, 0, 0)
        LOAD_CURSOR(arrow5, 0, 0)
        LOAD_CURSOR(arrow6, 0, 0)
        LOAD_CURSOR(arrow7, 0, 0)
        LOAD_CURSOR(attack, 0, 0)
        LOAD_CURSOR(backpack, 0, 0)
        LOAD_CURSOR(cantput, 0, 0)
        LOAD_CURSOR(cast, 0, 0)
        LOAD_CURSOR(default, 0, 0)
        LOAD_CURSOR(defend, 0, 0)
        LOAD_CURSOR(dice, 0, 0)
        LOAD_CURSOR(move, -16, -16)
        LOAD_CURSOR(patrol, 0, 0)
        LOAD_CURSOR(pickup, 0, 0)
        LOAD_CURSOR(sdefault, 0, 0)
        LOAD_CURSOR(select, 0, 0)
        LOAD_CURSOR(swarm, 0, 0)
        LOAD_CURSOR(town, 0, 0)
        LOAD_CURSOR(wait, 0, 0)

        #undef LOAD_CURSOR
    }

    void CursorSubsystem::set_cursor(cursor_state cursor) {
        current_cursor_ = cursor;
        current_frame_ = 0;
    }

    void CursorSubsystem::update() {
        auto current_sprite = sprites_[static_cast<size_t>(current_cursor_)];
        current_frame_ = (current_frame_ + 1) % current_sprite->frame_count();
    }

    void CursorSubsystem::render(SOASpriteRGB &background_sprite, const MouseState& mouse_state) {
        auto idx = static_cast<size_t>(current_cursor_);
        auto current_sprite = sprites_[idx];
        current_sprite->blit_on_sprite(
            background_sprite,
            mouse_state.mouse_x + ofsset_x_array_[idx],
            mouse_state.mouse_y + ofsset_y_array_[idx],
            current_frame_
        );
    }
}


