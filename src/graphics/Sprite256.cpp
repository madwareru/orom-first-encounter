#include <graphics/Sprite256.h>
#include <graphics/soaspritergb.h>

#include <util/macro_shared.h>

Sprite256::Sprite256(rage_of_mages_1_256_t* data) {
    frame_count_ = static_cast<uint16_t>(data->sprite_count());
    if(data->has_palette()) {
        auto pal = (data->inner_palette());
        for(uint16_t i = 0; i < 256; ++i) {
            uint32_t clr = (*pal)[i];
            palette_b_[i] = clr & 0xFF; clr /= 0x100;
            palette_g_[i] = clr & 0xFF; clr /= 0x100;
            palette_r_[i] = clr & 0xFF;
            if(palette_b_[i] < 127) {
                palette_b_[i] = palette_b_[i] * 2;
            } else {
                palette_b_[i] = 255;
            }
            if(palette_g_[i] < 127) {
                palette_g_[i] = palette_g_[i] * 2;
            } else {
                palette_g_[i] = 255;
            }
            if(palette_r_[i] < 127) {
                palette_r_[i] = palette_r_[i] * 2;
            } else {
                palette_r_[i] = 255;
            }
        }
    } else {
        for(uint16_t i = 0; i < 256; ++i) {
            palette_b_[i] = i & 0xFF;
            palette_g_[i] = i & 0xFF;
            palette_r_[i] = i & 0xFF;
        }
    }
    uint32_t overall_raw_size = 0;
    auto sprite_records = data->sprite_records();
    for(uint16_t i = 0; i < sprite_records->size(); ++i) {
        auto sprite_record = sprite_records->at(i);
        auto next_sprite_info = std::make_tuple(
            overall_raw_size,
            sprite_record->width(),
            sprite_record->height(),
            sprite_record->data_size()
        );
        frame_info_vector_.emplace_back(std::move(next_sprite_info));
        overall_raw_size += sprite_record->data_size();
    }
    buffer_raw_ = new uint8_t[overall_raw_size];
    uint32_t offset = 0;
    for(uint16_t i = 0; i < sprite_records->size(); ++i) {
        auto sprite_record = sprite_records->at(i);
        auto sprite_data = sprite_record->data();
        for(uint16_t j = 0; j < sprite_record->data_size(); ++j) {
            buffer_raw_[offset++] = static_cast<uint8_t>(sprite_data[j]);
        }
    }
}

Sprite256::~Sprite256() {
    delete [] buffer_raw_;
}

uint16_t Sprite256::frame_count() const {
    return frame_count_;
}

void Sprite256::blit_on_sprite_centered(SOASpriteRGB& other, int32_t x, int32_t y, uint16_t frame_number, int32_t off_x, int32_t off_y, int32_t fixed_w, int32_t fixed_h) {
    auto [__, width, height, ___] = frame_info_vector_[frame_number];
    blit_on_sprite(
        other,
        x - (width * off_x) / fixed_w,
        y - (height * off_y) / fixed_h,
        frame_number
    );
}

void Sprite256::blit_on_sprite(SOASpriteRGB& other, int32_t x, int32_t y, uint16_t frame_number) {
    const uint8_t BLANK_LINE = 0x40;
    const uint8_t EMPTY_AREA_BITS = 0xC0;
    const uint8_t CHUNK_SIZE_BITS = 0x3F;

    if(frame_number >= frame_count_) {
        frame_number %= frame_count_;
    }
    auto [offset, width, height, data_size] = frame_info_vector_[frame_number];
    auto sw = width;
    auto sh = height;
    auto raw = &buffer_raw_[offset];
    auto raw_size = data_size;
    other.lock([&](auto w, auto h, auto rbuf, auto gbuf, auto bbuf){
        uint8_t* buf = &raw[0];
        uint16_t w_drawn = 0;

        if(x >= 0 && y >= 0 && (static_cast<size_t>(x + sw) <= w) && (static_cast<size_t>(y + sh) <= h)) {
            size_t offset = static_cast<size_t>(y) * w + static_cast<size_t>(x);
            // render trivially without checks
            int i = 0;
            while(i < raw_size) {
                uint8_t ipx = *buf++;
                uint8_t is_empty_area_mask = ipx & EMPTY_AREA_BITS;
                uint8_t chunk_size = ipx & CHUNK_SIZE_BITS;
                ++i;

                if(is_empty_area_mask > 0) {
                    if(is_empty_area_mask == BLANK_LINE) {
                        offset += w * chunk_size;
                    } else {
                        w_drawn += chunk_size;
                        offset += chunk_size;
                        if(w_drawn >= sw) {
                            offset += w - sw;
                            w_drawn -= sw;
                        }
                    }
                    continue;
                }

                for(uint8_t j = 0; j < chunk_size; ++j) {
                    uint8_t palette_id = *buf++;

                    if(w_drawn >= sw) {
                        offset += w - sw;
                        w_drawn -= sw;
                    }

                    rbuf[offset] = palette_r_[palette_id];
                    gbuf[offset] = palette_g_[palette_id];
                    bbuf[offset] = palette_b_[palette_id];

                    offset++;
                    w_drawn++;
                }
                i += chunk_size;
            }
            return;
        }

        //since we can't be sure about borders we draw in more "pixely" way

        auto xx = x;
        auto yy = y;
        int i = 0;
        while(i < raw_size) {
            uint8_t ipx = *buf++;
            uint8_t is_empty_area_mask = ipx & EMPTY_AREA_BITS;
            uint8_t chunk_size = ipx & CHUNK_SIZE_BITS;
            ++i;

            if(is_empty_area_mask > 0) {
                if(is_empty_area_mask == BLANK_LINE) {
                    yy += chunk_size;
                } else {
                    w_drawn += chunk_size;
                    xx += chunk_size;
                    if(w_drawn >= sw) {
                        yy++;
                        xx -= sw;
                        w_drawn -= sw;
                    }
                }
                continue;
            }

            for(uint8_t j = 0; j < chunk_size; ++j) {
                uint8_t palette_id = *buf++;

                if(w_drawn >= sw) {
                    yy++;
                    xx -= sw;
                    w_drawn -= sw;
                }

                if(xx >= 0 && yy >= 0 && static_cast<size_t>(xx) < w && static_cast<size_t>(yy) < h) {
                    size_t offset = static_cast<size_t>(yy) * w + static_cast<size_t>(xx);
                    rbuf[offset] = palette_r_[palette_id];
                    gbuf[offset] = palette_g_[palette_id];
                    bbuf[offset] = palette_b_[palette_id];
                }
                xx++;
                w_drawn++;
            }
            i += chunk_size;
        }
    });
}
