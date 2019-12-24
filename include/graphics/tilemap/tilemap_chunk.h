#ifndef TILEMAP_CHUNK_H
#define TILEMAP_CHUNK_H

#include <cstdint>

struct TileCorners {
    uint8_t top_left_height;
    uint8_t top_right_height;
    uint8_t bottom_left_height;
    uint8_t bottom_right_height;
};

struct TileEntry {
    int32_t min_y;
    int32_t max_y;
    TileCorners corners;
    uint16_t tile_id;
    uint8_t tile_i;
    uint8_t tile_j;
};

#endif /* end of include guard: TILEMAP_CHUNK_H */
