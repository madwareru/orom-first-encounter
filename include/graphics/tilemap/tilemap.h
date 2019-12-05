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
    void add_chunk(TileMapChunk&& chunk);
    const std::vector<TileMapChunk>& get_chunks() const;
private:
    std::vector<TileMapChunk> tile_chunks_;
};

#endif /* end of include guard: TILEMAP_H */
