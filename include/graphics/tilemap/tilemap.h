#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include "tilemap_chunk.h"

struct TileMap {
    TileMap(size_t w, size_t h);
    TileMap(const TileMap&) = delete;
    TileMap& operator=(const TileMap&) = delete;
    TileMap(TileMap&&) = delete;
    TileMap& operator=(TileMap&&) = delete;
    size_t width() const;
    size_t height() const;
    void add_chunk(const TileMapChunk& chunk);
    const std::vector<TileMapChunk>& get_chunks() const;
    int32_t get_x_at_tile(size_t x, size_t y, uint8_t alpha_x, uint8_t alpha_y) const;
    int32_t get_y_at_tile(size_t x, size_t y, uint8_t alpha_x, uint8_t alpha_y) const;
private:
    size_t w_;
    size_t h_;
    std::vector<TileMapChunk> tile_chunks_;
};

#endif /* end of include guard: TILEMAP_H */
