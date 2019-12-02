#ifndef CURSOR_STATE_H_
#define CURSOR_STATE_H_

#include <cstdint>

namespace Game {
    const uint8_t cursor_count = 23;

    enum class cursor_state : uint8_t {
        c_arrow0 = 0,
        c_arrow1 = 1,
        c_arrow2 = 2,
        c_arrow3 = 3,
        c_arrow4 = 4,
        c_arrow5 = 5,
        c_arrow6 = 6,
        c_arrow7 = 7,
        c_attack = 8,
        c_backpack = 9,
        c_cantput = 10,
        c_cast = 11,
        c_default = 12,
        c_defend = 13,
        c_dice = 14,
        c_move = 15,
        c_patrol = 16,
        c_pickup = 17,
        c_sdefault = 18,
        c_select = 19,
        c_swarm = 20,
        c_town = 21,
        c_wait = 22
    };
}

#endif /* end of include guard: CURSOR_STATE_H_ */
