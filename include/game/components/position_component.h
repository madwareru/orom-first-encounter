#ifndef POSITION_COMPONENT_H__
#define POSITION_COMPONENT_H__

#include <cstdint>

/*
    Component which stores a unit or structure or map object position in
    fixed point manner, which means that lower byte is in fact a fraction
    inside the tile, and higher byte is a tile coordinate
*/

struct position_component {
    uint16_t x;
    uint16_t y;
};

#endif /* end of include guard: POSITION_COMPONENT_H__ */
