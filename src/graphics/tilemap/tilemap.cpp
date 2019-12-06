#include <graphics/tilemap/tilemap.h>

TileMap::TileMap(size_t w, size_t h) {
    tile_chunks_.reserve(w * h / 8);
}

const std::vector<TileMapChunk>& TileMap::get_chunks() const {
    return tile_chunks_;
}

void TileMap::add_chunk(const TileMapChunk& chunk) {
    tile_chunks_.emplace_back(chunk);
}
