#include <graphics/tilemap/tilemap.h>
#include <util/macro_shared.h>

TileMap::TileMap(size_t w, size_t h): w_{w}, h_{h} {
    tiles_ = new TileEntry[w * h];
}

TileMap::~TileMap() {
    delete [] tiles_;
}

size_t TileMap::width() const{
    return w_;
}

size_t TileMap::height() const{
    return h_;
}

TileEntry& TileMap::get_tile(size_t i, size_t j) {
    return tiles_[i + j * w_];
}

const TileEntry& TileMap::get_tile(size_t i, size_t j) const {
    return tiles_[i + j * w_];
}

int32_t TileMap::get_x_at_tile(size_t x, size_t y, uint8_t alpha_x, uint8_t alpha_y) const {
    return (static_cast<int32_t>(x) - 8) * 32 + alpha_x;
}

int32_t TileMap::get_y_at_tile(size_t x, size_t y, uint8_t alpha_x, uint8_t alpha_y) const {
    const auto& chunk = get_tile(x, y);
    const auto& corners = chunk.corners;

    auto tlh = corners.top_left_height;
    auto trh = corners.top_right_height;
    auto blh = corners.bottom_left_height;
    auto brh = corners.bottom_right_height;

    auto lerp_top = 32 * tlh + (trh - tlh) * alpha_x;
    auto lerp_bottom = 32 * blh + (brh - blh) * alpha_x;
    auto lerp_center = (32 * lerp_top + (lerp_bottom - lerp_top) * alpha_y) / 1024;

    auto center_y = (static_cast<int32_t>(y) - 8) * 32 + alpha_y;

    return center_y - lerp_center;
}
