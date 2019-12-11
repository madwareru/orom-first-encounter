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

int32_t TileMap::get_x_at_tile(size_t x, size_t y, uint8_t alpha_x, uint8_t alpha_y) const {
    return (static_cast<int32_t>(x) - 8) * 32 + alpha_x;
}

int32_t TileMap::get_y_at_tile(size_t x, size_t y, uint8_t alpha_x, uint8_t alpha_y) const {
    size_t chx = x / 8;
    size_t chk_id = (w_ / 8) * y + chx;
    LOG_ASSERT(chk_id < tile_chunks_.size())
    auto chunk = tile_chunks_[chk_id];

    size_t off_x = (x % 8) * 2;

    int32_t tlh = static_cast<int32_t>(chunk.top_heights[off_x]);
    int32_t blh = static_cast<int32_t>(chunk.bottom_heights[off_x++]);
    int32_t trh = static_cast<int32_t>(chunk.top_heights[off_x]);
    int32_t brh = static_cast<int32_t>(chunk.bottom_heights[off_x]);

    int32_t lerp_top = 32 * tlh + (trh - tlh) * alpha_x;
    int32_t lerp_bottom = 32 * blh + (brh - blh) * alpha_x;
    int32_t lerp_center = (32 * lerp_top + (lerp_bottom - lerp_top) * alpha_y) / 1024;

    auto center_y = (static_cast<int32_t>(y) - 8) * 32 + alpha_y;

    return center_y - lerp_center;
}

void TileMap::add_chunk(const TileMapChunk& chunk) {
    tile_chunks_.emplace_back(chunk);
}
