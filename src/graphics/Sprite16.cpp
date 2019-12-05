#include <graphics/Sprite16.h>
#include <graphics/soaspritergb.h>

#include <util/macro_shared.h>
#include <loaders/ksy/rage_of_mages_1_16.h>

static uint8_t font_palette_lookup_b[256] = {
    0x20,
    0x23,
    0x27,
    0x2B,
    0x2F,
    0x33,
    0x38,
    0x3D,
    0x43,
    0x49,
    0x50,
    0x57,
    0x5F,
    0x68,
    0x71,
    0x7B,
    0x15,
    0x17,
    0x19,
    0x1C,
    0x1F,
    0x22,
    0x25,
    0x29,
    0x2D,
    0x31,
    0x36,
    0x3B,
    0x41,
    0x47,
    0x4E,
    0x55,
    0x23,
    0x27,
    0x2B,
    0x2F,
    0x34,
    0x39,
    0x3E,
    0x44,
    0x4A,
    0x51,
    0x58,
    0x60,
    0x69,
    0x72,
    0x7C,
    0x87,
    0x40,
    0x46,
    0x4C,
    0x53,
    0x5B,
    0x63,
    0x6C,
    0x76,
    0x81,
    0x8C,
    0x98,
    0xA5,
    0xB3,
    0xC3,
    0xD4,
    0xE7,
    0x12,
    0x14,
    0x16,
    0x18,
    0x1B,
    0x1E,
    0x21,
    0x24,
    0x28,
    0x2C,
    0x30,
    0x35,
    0x3A,
    0x3F,
    0x45,
    0x4B,
    0x11,
    0x13,
    0x15,
    0x17,
    0x1A,
    0x1D,
    0x20,
    0x23,
    0x27,
    0x2B,
    0x2F,
    0x34,
    0x39,
    0x3E,
    0x44,
    0x4A,
    0x26,
    0x2A,
    0x2E,
    0x32,
    0x37,
    0x3C,
    0x42,
    0x48,
    0x4F,
    0x56,
    0x5E,
    0x67,
    0x70,
    0x7A,
    0x85,
    0x91,
    0x35,
    0x3A,
    0x3F,
    0x45,
    0x4B,
    0x52,
    0x5A,
    0x62,
    0x6B,
    0x75,
    0x80,
    0x8B,
    0x97,
    0xA4,
    0xB2,
    0xC2,
    0x40,
    0x46,
    0x4C,
    0x53,
    0x5B,
    0x63,
    0x6C,
    0x76,
    0x81,
    0x8C,
    0x98,
    0xA5,
    0xB3,
    0xC3,
    0xD4,
    0xE7,
    0x40,
    0x46,
    0x4C,
    0x53,
    0x5B,
    0x63,
    0x6C,
    0x76,
    0x81,
    0x8C,
    0x98,
    0xA5,
    0xB3,
    0xC3,
    0xD4,
    0xE7,
    0x15,
    0x17,
    0x19,
    0x1C,
    0x1F,
    0x22,
    0x25,
    0x29,
    0x2D,
    0x31,
    0x36,
    0x3B,
    0x41,
    0x47,
    0x4E,
    0x55,
    0x35,
    0x3A,
    0x3F,
    0x45,
    0x4B,
    0x52,
    0x5A,
    0x62,
    0x6B,
    0x75,
    0x80,
    0x8B,
    0x97,
    0xA4,
    0xB2,
    0xC2,
    0x2E,
    0x32,
    0x37,
    0x3C,
    0x42,
    0x48,
    0x4F,
    0x56,
    0x5E,
    0x66,
    0x6F,
    0x79,
    0x84,
    0x90,
    0x9D,
    0xAB,
    0x11,
    0x13,
    0x15,
    0x17,
    0x1A,
    0x1D,
    0x20,
    0x23,
    0x27,
    0x2B,
    0x2F,
    0x34,
    0x39,
    0x3E,
    0x44,
    0x4A,
    0x15,
    0x17,
    0x1A,
    0x1D,
    0x20,
    0x23,
    0x26,
    0x2A,
    0x2E,
    0x32,
    0x37,
    0x3C,
    0x42,
    0x48,
    0x4F,
    0x56,
    0x46,
    0x4C,
    0x53,
    0x5B,
    0x63,
    0x6C,
    0x76,
    0x81,
    0x8D,
    0x9A,
    0xA8,
    0xB7,
    0xC7,
    0xD8,
    0xEB,
    0xFF
};

static uint8_t font_palette_lookup_g[256] = {
    0x15,
    0x17,
    0x19,
    0x1C,
    0x1F,
    0x22,
    0x25,
    0x29,
    0x2D,
    0x31,
    0x36,
    0x3B,
    0x41,
    0x47,
    0x4E,
    0x55,
    0x27,
    0x2B,
    0x2F,
    0x34,
    0x39,
    0x3E,
    0x44,
    0x4A,
    0x51,
    0x58,
    0x60,
    0x69,
    0x72,
    0x7C,
    0x87,
    0x93,
    0x40,
    0x46,
    0x4C,
    0x53,
    0x5B,
    0x63,
    0x6C,
    0x76,
    0x81,
    0x8C,
    0x98,
    0xA5,
    0xB3,
    0xC3,
    0xD4,
    0xE7,
    0x30,
    0x35,
    0x3A,
    0x40,
    0x46,
    0x4C,
    0x53,
    0x5B,
    0x63,
    0x6C,
    0x76,
    0x81,
    0x8D,
    0x9A,
    0xA8,
    0xB7,
    0x11,
    0x13,
    0x15,
    0x17,
    0x1A,
    0x1D,
    0x20,
    0x23,
    0x27,
    0x2B,
    0x2F,
    0x34,
    0x39,
    0x3E,
    0x44,
    0x4A,
    0x28,
    0x2C,
    0x30,
    0x35,
    0x3A,
    0x40,
    0x46,
    0x4D,
    0x54,
    0x5C,
    0x64,
    0x6D,
    0x77,
    0x82,
    0x8E,
    0x9B,
    0x35,
    0x3A,
    0x3F,
    0x45,
    0x4B,
    0x52,
    0x5A,
    0x62,
    0x6B,
    0x75,
    0x80,
    0x8B,
    0x97,
    0xA4,
    0xB2,
    0xC2,
    0x20,
    0x23,
    0x27,
    0x2B,
    0x2F,
    0x34,
    0x39,
    0x3E,
    0x44,
    0x4A,
    0x51,
    0x58,
    0x60,
    0x69,
    0x72,
    0x7C,
    0x15,
    0x17,
    0x19,
    0x1C,
    0x1F,
    0x22,
    0x25,
    0x29,
    0x2D,
    0x31,
    0x36,
    0x3B,
    0x41,
    0x47,
    0x4E,
    0x55,
    0x15,
    0x17,
    0x19,
    0x1C,
    0x1F,
    0x22,
    0x25,
    0x29,
    0x2D,
    0x31,
    0x36,
    0x3B,
    0x41,
    0x47,
    0x4E,
    0x55,
    0x3A,
    0x3F,
    0x45,
    0x4B,
    0x52,
    0x5A,
    0x62,
    0x6B,
    0x75,
    0x7F,
    0x8A,
    0x96,
    0xA3,
    0xB1,
    0xC1,
    0xD2,
    0x11,
    0x13,
    0x15,
    0x17,
    0x1A,
    0x1D,
    0x20,
    0x23,
    0x27,
    0x2B,
    0x2F,
    0x34,
    0x39,
    0x3E,
    0x44,
    0x4A,
    0x11,
    0x13,
    0x15,
    0x17,
    0x1A,
    0x1D,
    0x20,
    0x23,
    0x27,
    0x2B,
    0x2F,
    0x34,
    0x39,
    0x3E,
    0x44,
    0x4A,
    0x35,
    0x3A,
    0x3F,
    0x45,
    0x4B,
    0x52,
    0x5A,
    0x62,
    0x6B,
    0x75,
    0x80,
    0x8B,
    0x97,
    0xA4,
    0xB2,
    0xC2,
    0x35,
    0x3A,
    0x3F,
    0x45,
    0x4B,
    0x52,
    0x5A,
    0x62,
    0x6B,
    0x75,
    0x80,
    0x8B,
    0x97,
    0xA4,
    0xB2,
    0xC2,
    0x46,
    0x4C,
    0x53,
    0x5B,
    0x63,
    0x6C,
    0x76,
    0x81,
    0x8D,
    0x9A,
    0xA8,
    0xB7,
    0xC7,
    0xD8,
    0xEB,
    0xFF
};

static uint8_t font_palette_lookup_r[256] = {
    0x40,
    0x46,
    0x4C,
    0x53,
    0x5B,
    0x63,
    0x6C,
    0x76,
    0x81,
    0x8C,
    0x98,
    0xA5,
    0xB3,
    0xC3,
    0xD4,
    0xE7,
    0x40,
    0x46,
    0x4C,
    0x53,
    0x5B,
    0x63,
    0x6C,
    0x76,
    0x81,
    0x8C,
    0x98,
    0xA5,
    0xB3,
    0xC3,
    0xD4,
    0xE7,
    0x15,
    0x17,
    0x19,
    0x1C,
    0x1F,
    0x22,
    0x25,
    0x29,
    0x2D,
    0x31,
    0x36,
    0x3B,
    0x41,
    0x47,
    0x4E,
    0x55,
    0x15,
    0x17,
    0x19,
    0x1C,
    0x1F,
    0x22,
    0x25,
    0x29,
    0x2D,
    0x31,
    0x36,
    0x3B,
    0x41,
    0x47,
    0x4E,
    0x55,
    0x35,
    0x3A,
    0x3F,
    0x45,
    0x4B,
    0x52,
    0x5A,
    0x62,
    0x6B,
    0x75,
    0x80,
    0x8B,
    0x97,
    0xA4,
    0xB2,
    0xC2,
    0x35,
    0x3A,
    0x3F,
    0x45,
    0x4B,
    0x52,
    0x5A,
    0x62,
    0x6B,
    0x75,
    0x80,
    0x8B,
    0x97,
    0xA4,
    0xB2,
    0xC2,
    0x11,
    0x13,
    0x15,
    0x17,
    0x1A,
    0x1D,
    0x20,
    0x23,
    0x27,
    0x2B,
    0x2F,
    0x34,
    0x39,
    0x3E,
    0x44,
    0x4A,
    0x11,
    0x13,
    0x15,
    0x17,
    0x1A,
    0x1D,
    0x20,
    0x23,
    0x27,
    0x2B,
    0x2F,
    0x34,
    0x39,
    0x3E,
    0x44,
    0x4A,
    0x20,
    0x23,
    0x26,
    0x2A,
    0x2E,
    0x32,
    0x37,
    0x3C,
    0x42,
    0x48,
    0x4F,
    0x56,
    0x5E,
    0x67,
    0x70,
    0x7A,
    0x3D,
    0x43,
    0x49,
    0x50,
    0x57,
    0x5F,
    0x68,
    0x71,
    0x7B,
    0x86,
    0x92,
    0x9F,
    0xAD,
    0xBC,
    0xCC,
    0xDE,
    0x40,
    0x46,
    0x4C,
    0x53,
    0x5B,
    0x63,
    0x6C,
    0x76,
    0x81,
    0x8C,
    0x98,
    0xA5,
    0xB3,
    0xC3,
    0xD4,
    0xE7,
    0x23,
    0x27,
    0x2B,
    0x2F,
    0x34,
    0x39,
    0x3E,
    0x44,
    0x4A,
    0x51,
    0x58,
    0x60,
    0x69,
    0x72,
    0x7C,
    0x87,
    0x35,
    0x3A,
    0x3F,
    0x45,
    0x4B,
    0x52,
    0x5A,
    0x62,
    0x6B,
    0x75,
    0x80,
    0x8B,
    0x97,
    0xA4,
    0xB2,
    0xC2,
    0x30,
    0x35,
    0x3A,
    0x40,
    0x46,
    0x4C,
    0x53,
    0x5B,
    0x63,
    0x6C,
    0x76,
    0x81,
    0x8D,
    0x99,
    0xA6,
    0xB5,
    0x11,
    0x13,
    0x15,
    0x17,
    0x1A,
    0x1D,
    0x20,
    0x23,
    0x27,
    0x2B,
    0x2F,
    0x34,
    0x39,
    0x3E,
    0x44,
    0x4A,
    0x46,
    0x4C,
    0x53,
    0x5B,
    0x63,
    0x6C,
    0x76,
    0x81,
    0x8D,
    0x9A,
    0xA8,
    0xB7,
    0xC7,
    0xD8,
    0xEB,
    0xFF
};

Sprite16::Sprite16(rage_of_mages_1_16_t* data) {
    frame_count_ = static_cast<uint16_t>(data->sprite_count());
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

Sprite16::~Sprite16() {
    delete [] buffer_raw_;
}

uint16_t Sprite16::frame_count() const {
    return frame_count_;
}

void Sprite16::blit_on_sprite(SOASpriteRGB& other, int32_t x, int32_t y, uint16_t frame_number) {
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
    other.mutate([&](auto w, auto h, auto rbuf, auto gbuf, auto bbuf){
        uint8_t* buf = &raw[0];
        uint16_t w_drawn = 0;

        uint8_t dest_r = 255;
        uint8_t dest_g = 255;
        uint8_t dest_b = 255;

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
                    uint8_t psh = *buf++;

                    uint8_t alpha0 = psh & 0xF;
                    uint8_t alpha1 = psh / 0x10;

                    if(w_drawn >= sw) {
                        offset += w - sw;
                        w_drawn -= sw;
                    }

                    uint8_t one_minus_alpha = 0xF - alpha0;

                    rbuf[offset] = (rbuf[offset] * one_minus_alpha + dest_r * alpha0) / 0x10;
                    gbuf[offset] = (gbuf[offset] * one_minus_alpha + dest_g * alpha0) / 0x10;
                    bbuf[offset] = (bbuf[offset] * one_minus_alpha + dest_b * alpha0) / 0x10;

                    offset++;
                    w_drawn++;

                    if((alpha1 == 0) && (j == chunk_size - 1)) {
                        continue;
                    }

                    if(w_drawn >= sw) {
                        offset += w - sw;
                        w_drawn -= sw;
                    }

                    one_minus_alpha = 0xF - alpha1;

                    rbuf[offset] = (rbuf[offset] * one_minus_alpha + dest_r * alpha1) / 0x10;
                    gbuf[offset] = (gbuf[offset] * one_minus_alpha + dest_g * alpha1) / 0x10;
                    bbuf[offset] = (bbuf[offset] * one_minus_alpha + dest_b * alpha1) / 0x10;

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
                uint8_t psh = *buf++;

                uint8_t alpha0 = psh & 0xF;
                uint8_t alpha1 = psh / 0x10;

                if(w_drawn >= sw) {
                    yy++;
                    xx -= sw;
                    w_drawn -= sw;
                }

                if(xx >= 0 && yy >= 0 && static_cast<size_t>(xx) < w && static_cast<size_t>(yy) < h) {
                    size_t offset = static_cast<size_t>(yy) * w + static_cast<size_t>(xx);

                    uint8_t one_minus_alpha = 0xF - alpha0;

                    rbuf[offset] = (rbuf[offset] * one_minus_alpha + dest_r * alpha0) / 0x10;
                    gbuf[offset] = (gbuf[offset] * one_minus_alpha + dest_g * alpha0) / 0x10;
                    bbuf[offset] = (bbuf[offset] * one_minus_alpha + dest_b * alpha0) / 0x10;
                }
                xx++;
                w_drawn++;

                if((alpha1 == 0) && (j == chunk_size - 1)) {
                    continue;
                }

                if(w_drawn >= sw) {
                    yy++;
                    xx -= sw;
                    w_drawn -= sw;
                }

                if(xx >= 0 && yy >= 0 && static_cast<size_t>(xx) < w && static_cast<size_t>(yy) < h) {
                    size_t offset = static_cast<size_t>(yy) * w + static_cast<size_t>(xx);

                    uint8_t one_minus_alpha = 0xF - alpha1;

                    rbuf[offset] = (rbuf[offset] * one_minus_alpha + dest_r * alpha1) / 0x10;
                    gbuf[offset] = (gbuf[offset] * one_minus_alpha + dest_g * alpha1) / 0x10;
                    bbuf[offset] = (bbuf[offset] * one_minus_alpha + dest_b * alpha1) / 0x10;
                }
                xx++;
                w_drawn++;
            }
            i += chunk_size;
        }
    });
}

void Sprite16::blit_on_sprite(SOASpriteRGB& other, int32_t x, int32_t y, uint16_t frame_number, uint8_t palette_id) {
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
    other.mutate([&](auto w, auto h, auto rbuf, auto gbuf, auto bbuf){
        uint8_t* buf = &raw[0];
        uint16_t w_drawn = 0;

        uint8_t* pal_r = &font_palette_lookup_r[16 * (palette_id%16)];
        uint8_t* pal_g = &font_palette_lookup_g[16 * (palette_id%16)];
        uint8_t* pal_b = &font_palette_lookup_b[16 * (palette_id%16)];

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
                    uint8_t psh = *buf++;

                    uint8_t alpha0 = psh & 0xF;
                    uint8_t alpha1 = psh / 0x10;

                    if(w_drawn >= sw) {
                        offset += w - sw;
                        w_drawn -= sw;
                    }

                    uint8_t one_minus_alpha = 0xF - alpha0;

                    rbuf[offset] = pal_r[alpha0];
                    gbuf[offset] = pal_g[alpha0];
                    bbuf[offset] = pal_b[alpha0];

                    offset++;
                    w_drawn++;

                    if((alpha1 == 0) && (j == chunk_size - 1)) {
                        continue;
                    }

                    if(w_drawn >= sw) {
                        offset += w - sw;
                        w_drawn -= sw;
                    }

                    one_minus_alpha = 0xF - alpha1;

                    rbuf[offset] = pal_r[alpha1];
                    gbuf[offset] = pal_g[alpha1];
                    bbuf[offset] = pal_b[alpha1];

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
                uint8_t psh = *buf++;

                uint8_t alpha0 = psh & 0xF;
                uint8_t alpha1 = psh / 0x10;

                if(w_drawn >= sw) {
                    yy++;
                    xx -= sw;
                    w_drawn -= sw;
                }

                if(xx >= 0 && yy >= 0 && static_cast<size_t>(xx) < w && static_cast<size_t>(yy) < h) {
                    size_t offset = static_cast<size_t>(yy) * w + static_cast<size_t>(xx);

                    uint8_t one_minus_alpha = 0xF - alpha0;

                    rbuf[offset] = pal_r[alpha0];
                    gbuf[offset] = pal_g[alpha0];
                    bbuf[offset] = pal_b[alpha0];
                }
                xx++;
                w_drawn++;

                if((alpha1 == 0) && (j == chunk_size - 1)) {
                    continue;
                }

                if(w_drawn >= sw) {
                    yy++;
                    xx -= sw;
                    w_drawn -= sw;
                }

                if(xx >= 0 && yy >= 0 && static_cast<size_t>(xx) < w && static_cast<size_t>(yy) < h) {
                    size_t offset = static_cast<size_t>(yy) * w + static_cast<size_t>(xx);

                    uint8_t one_minus_alpha = 0xF - alpha1;

                    rbuf[offset] = pal_r[alpha1];
                    gbuf[offset] = pal_g[alpha1];
                    bbuf[offset] = pal_b[alpha1];
                }
                xx++;
                w_drawn++;
            }
            i += chunk_size;
        }
    });
}
