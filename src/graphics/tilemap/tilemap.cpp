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
    size_t chk_id = (w_ * y + x) / 8;
    auto chunk = tile_chunks_[chk_id];

    size_t off_x = (x & 0x7) * 2;

    auto tlh = chunk.top_heights[off_x];
    auto blh = chunk.bottom_heights[off_x++];
    auto trh = chunk.top_heights[off_x];
    auto brh = chunk.bottom_heights[off_x];

    auto lerp_top = 32 * tlh + (trh - tlh) * alpha_x;
    auto lerp_bottom = 32 * blh + (brh - blh) * alpha_x;
    auto lerp_center = (32 * lerp_top + (lerp_bottom - lerp_top) * alpha_y) / 1024;

    auto center_y = (static_cast<int32_t>(y) - 8) * 32 + alpha_y;

    return center_y - lerp_center;
}

void TileMap::add_chunk(const TileMapChunk& chunk) {
    tile_chunks_.emplace_back(chunk);
}
