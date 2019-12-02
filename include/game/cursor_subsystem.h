#ifndef CURSOR_SUBSYSTEM_H_
#define CURSOR_SUBSYSTEM_H_

#include <game/cursor_state.h>
#include <array>
#include <memory>
#include <cstdint>

struct Sprite16a;
struct SOASpriteRGB;
struct ResourceFile;
struct MouseState;

namespace Game {
    struct CursorSubsystem {
        CursorSubsystem(std::shared_ptr<ResourceFile> graphic_resources, Game::cursor_state initial_cursor);
        void update(const MouseState& mouse_state);
        void render(SOASpriteRGB &background_sprite);
    private:
        std::array<int16_t, Game::cursor_count> ofsset_x_array_;
        std::array<int16_t, Game::cursor_count> ofsset_y_array_;
        std::array<std::shared_ptr<Sprite16a>, Game::cursor_count> sprites_;
        cursor_state current_cursor_;
        uint16_t mouse_x_;
        uint16_t mouse_y_;
    };
}

#endif /* end of include guard: CURSOR_SUBSYSTEM_H_ */
