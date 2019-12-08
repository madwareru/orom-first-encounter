#include <graphics/tilemap/tilemap.h>

TileMap::TileMap(size_t w, size_t h): w_{w}, h_{h} {
    tile_chunks_.reserve(w * h / 8);
}

size_t TileMap::width() const{
    return w_;
}

size_t TileMap::height() const{
    return h_;
}

const std::vector<TileMapChunk>& TileMap::get_chunks() const {
    return tile_chunks_;
}

void TileMap::add_chunk(const TileMapChunk& chunk) {
    tile_chunks_.emplace_back(chunk);
}
