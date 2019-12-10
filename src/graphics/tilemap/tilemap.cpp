#include <graphics/tilemap/tilemap.h>
#include <util/macro_shared.h>

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

const int32_t TileMap::get_x_at_tile(size_t x, size_t y, uint8_t alpha_x, uint8_t alpha_y) const {
    return (static_cast<int32_t>(x) - 8) * 32 + alpha_x;
}

const int32_t TileMap::get_y_at_tile(size_t x, size_t y, uint8_t alpha_x, uint8_t alpha_y) const {
    size_t chx = x / 8;
    size_t chk_id = (w_ / 8) * y + x;
    LOG_ASSERT(chk_id < tile_chunks_.size())
    auto chunk = tile_chunks_[chk_id];

    size_t off_x = (x % 8) * 2;

    int32_t tlh = -static_cast<int32_t>(chunk.top_heights[off_x]);
    int32_t trh = -static_cast<int32_t>(chunk.top_heights[off_x+1]);
    int32_t blh = 32 -static_cast<int32_t>(chunk.bottom_heights[off_x]);
    int32_t brh = 32 -static_cast<int32_t>(chunk.bottom_heights[off_x+1]);

    int32_t lerp_top = (tlh * (31 - alpha_x) + trh * (alpha_x)) / 32;
    int32_t lerp_bottom = (blh * (31 - alpha_x) + brh * (alpha_x)) / 32;
    return (lerp_top * (31 - alpha_y) + lerp_bottom * (alpha_y)) / 32 + (static_cast<int32_t>(y) - 8) * 32;
}

void TileMap::add_chunk(const TileMapChunk& chunk) {
    tile_chunks_.emplace_back(chunk);
}
