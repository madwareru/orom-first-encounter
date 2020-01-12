#include <graphics/soaspritergb.h>
#include <emmintrin.h>
#include <iostream>

SOASpritePal::SOASpritePal(size_t w, size_t h): width_{w}, height_{h} {
    buffer_raw_ = new uint8_t[w * h + 8 + 0x3000];
    buffer_ = (reinterpret_cast<int64_t>(&buffer_raw_[0]) % 16 == 0)
            ? &buffer_raw_[0]
            : &buffer_raw_[8];
    pal_r_ = buffer_ + w*h;
    pal_g_ = pal_r_ + 0x1000;
    pal_b_ = pal_g_ + 0x1000;
}
SOASpritePal::~SOASpritePal() {
    delete [] buffer_raw_;
}

const uint8_t* SOASpritePal::blue_palette() const {
    return pal_b_;
}
const uint8_t* SOASpritePal::green_palette() const {
    return pal_g_;
}
const uint8_t* SOASpritePal::red_palette() const {
    return pal_r_;
}
const uint8_t* SOASpritePal::buffer() const {
    return buffer_;
}

SOASpriteRGB::SOASpriteRGB(size_t w, size_t h): width_{w}, height_{h} {
    r_buffer_raw_ = new uint8_t[w * h + 8];
    g_buffer_raw_ = new uint8_t[w * h + 8];
    b_buffer_raw_ = new uint8_t[w * h + 8];

    r_buffer_ = (reinterpret_cast<int64_t>(&r_buffer_raw_[0]) % 16 == 0)
        ? &r_buffer_raw_[0]
        : &r_buffer_raw_[8];

    g_buffer_ = (reinterpret_cast<int64_t>(&g_buffer_raw_[0]) % 16 == 0)
        ? &g_buffer_raw_[0]
        : &g_buffer_raw_[8];

    b_buffer_ = (reinterpret_cast<int64_t>(&b_buffer_raw_[0]) % 16 == 0)
        ? &b_buffer_raw_[0]
        : &b_buffer_raw_[8];
}

SOASpriteRGB::~SOASpriteRGB() {
    delete [] b_buffer_raw_;
    delete [] g_buffer_raw_;
    delete [] r_buffer_raw_;
}

size_t SOASpriteRGB::width() const {
    return width_;
}
size_t SOASpriteRGB::height() const {
    return height_;
}

uint8_t SOASpriteRGB::get_mask_pixel(size_t x, size_t y) const {
    return r_buffer_[x + y * width_];
}

void SOASpriteRGB::blit_on_opengl_buffer(uint8_t* dest_cbuf, uint16_t dw, uint16_t dh){
    uint8_t* b_data = &b_buffer_[0];
    uint8_t* g_data = &g_buffer_[0];
    uint8_t* r_data = &r_buffer_[0];
    uint8_t* d_data = &dest_cbuf[0];

    __m128i zero_batch = _mm_set1_epi8(0);

    for(size_t i = dw * dh; i; i -= 16) {
        auto bd = _mm_loadu_si128(reinterpret_cast<__m128i*>(b_data));
        auto gd = _mm_loadu_si128(reinterpret_cast<__m128i*>(g_data));
        auto rd = _mm_loadu_si128(reinterpret_cast<__m128i*>(r_data));

        auto m_r_b = _mm_unpacklo_epi8(rd, bd);
        auto m_g_a = _mm_unpacklo_epi8(gd, zero_batch);
        auto m_r_b_hi = _mm_unpackhi_epi8(rd, bd);
        auto m_g_a_hi = _mm_unpackhi_epi8(gd, zero_batch);

        _mm_storeu_si128(reinterpret_cast<__m128i*>(d_data), _mm_unpacklo_epi8(m_r_b, m_g_a));
        d_data += 16;
        _mm_storeu_si128(reinterpret_cast<__m128i*>(d_data), _mm_unpackhi_epi8(m_r_b, m_g_a));
        d_data += 16;
        _mm_storeu_si128(reinterpret_cast<__m128i*>(d_data), _mm_unpacklo_epi8(m_r_b_hi, m_g_a_hi));
        d_data += 16;
        _mm_storeu_si128(reinterpret_cast<__m128i*>(d_data), _mm_unpackhi_epi8(m_r_b_hi, m_g_a_hi));
        d_data += 16;

        b_data += 16;
        g_data += 16;
        r_data += 16;
    }
}

void SOASpriteRGB::blit_on_sprite(SOASpriteRGB& dsprite, int16_t x, int16_t y) {
    if((x < 0) || (y < 0)){
        if((x < 0) && (static_cast<size_t>(-x) >= width_)) {
            return;
        }
        if((y < 0) && (static_cast<size_t>(-y) >= height_)) {
            return;
        }
        size_t sx = (x < 0) ? static_cast<size_t>(-x) : 0;
        size_t sy = (y < 0) ? static_cast<size_t>(-y) : 0;
        size_t dx = (x < 0) ? 0 : static_cast<size_t>(x);
        size_t dy = (y < 0) ? 0 : static_cast<size_t>(y);
        blit_on_sprite(dsprite, dx, dy, sx, sy, width_ - sx, height_ - sy);
        return;
    }

    const size_t sw = width_;
    const size_t sh = height_;
    auto bbuf = b_buffer_;
    auto gbuf = g_buffer_;
    auto rbuf = r_buffer_;
    dsprite.lock([&](auto dw, auto dh, auto dr_buf, auto dg_buf, auto db_buf) {
        if(x >= dw || y >= dh) {
            return;
        }

        size_t span_width = dw - x;
        if(span_width > sw) {
            span_width = sw;
        }

        size_t span16_count = span_width / 16;
        span_width %= 16;

        size_t span_count = dh - y;
        if(span_count > sh) {
            span_count = sh;
        }

        uint8_t* b_data_l = &bbuf[0];
        uint8_t* g_data_l = &gbuf[0];
        uint8_t* r_data_l = &rbuf[0];

        uint8_t* db_data_l = &db_buf[x + dw * y];
        uint8_t* dg_data_l = &dg_buf[x + dw * y];
        uint8_t* dr_data_l = &dr_buf[x + dw * y];

        for(size_t j = span_count; j; --j) {
            uint8_t* b_data = b_data_l;
            uint8_t* g_data = g_data_l;
            uint8_t* r_data = r_data_l;

            uint8_t* db_data = db_data_l;
            uint8_t* dg_data = dg_data_l;
            uint8_t* dr_data = dr_data_l;

            for(size_t i = span16_count; i; --i) {
                _mm_storeu_si128(reinterpret_cast<__m128i*>(db_data), _mm_loadu_si128(reinterpret_cast<__m128i*>(b_data)));
                _mm_storeu_si128(reinterpret_cast<__m128i*>(dg_data), _mm_loadu_si128(reinterpret_cast<__m128i*>(g_data)));
                _mm_storeu_si128(reinterpret_cast<__m128i*>(dr_data), _mm_loadu_si128(reinterpret_cast<__m128i*>(r_data)));
                db_data += 16;
                dg_data += 16;
                dr_data += 16;

                b_data += 16;
                g_data += 16;
                r_data += 16;
            }

            for(size_t i = span_width; i; --i) {
                *db_data++ = *b_data++;
            }

            for(size_t i = span_width; i; --i) {
                *dg_data++ = *g_data++;
            }

            for(size_t i = span_width; i; --i) {
                *dr_data++ = *r_data++;
            }

            b_data_l += sw;
            g_data_l += sw;
            r_data_l += sw;

            db_data_l += dw;
            dg_data_l += dw;
            dr_data_l += dw;
        }
    });
}

void SOASpriteRGB::blit_on_sprite(SOASpriteRGB& dsprite, size_t dx, size_t dy, size_t sx, size_t sy, size_t w, size_t h) {
    if((sx >= width_) || (sy >= height_)) return;
    const size_t sw = (sx + w > width_) ? width_ - sx : w;
    const size_t sh = (sy + h > height_) ? height_ - sy : h;
    const size_t src_stride_start = sx + sy * width_;
    auto bbuf = b_buffer_;
    auto gbuf = g_buffer_;
    auto rbuf = r_buffer_;
    dsprite.lock([&](auto dw, auto dh, auto dr_buf, auto dg_buf, auto db_buf) {
        if(dx >= dw || dy >= dh) {
            return;
        }

        size_t span_width = dw - dx;
        if(span_width > sw) {
            span_width = sw;
        }

        size_t span16_count = span_width / 16;
        span_width %= 16;

        size_t span_count = dh - dy;
        if(span_count > sh) {
            span_count = sh;
        }

        uint8_t* b_data_l = &bbuf[src_stride_start];
        uint8_t* g_data_l = &gbuf[src_stride_start];
        uint8_t* r_data_l = &rbuf[src_stride_start];

        const size_t dst_stride_start = dx + dw * dy;

        uint8_t* db_data_l = &db_buf[dst_stride_start];
        uint8_t* dg_data_l = &dg_buf[dst_stride_start];
        uint8_t* dr_data_l = &dr_buf[dst_stride_start];

        for(size_t j = span_count; j; --j) {
            uint8_t* b_data = b_data_l;
            uint8_t* g_data = g_data_l;
            uint8_t* r_data = r_data_l;

            uint8_t* db_data = db_data_l;
            uint8_t* dg_data = dg_data_l;
            uint8_t* dr_data = dr_data_l;

            for(size_t i = span16_count; i; --i) {
                _mm_storeu_si128(reinterpret_cast<__m128i*>(db_data), _mm_loadu_si128(reinterpret_cast<__m128i*>(b_data)));
                _mm_storeu_si128(reinterpret_cast<__m128i*>(dg_data), _mm_loadu_si128(reinterpret_cast<__m128i*>(g_data)));
                _mm_storeu_si128(reinterpret_cast<__m128i*>(dr_data), _mm_loadu_si128(reinterpret_cast<__m128i*>(r_data)));
                db_data += 16;
                dg_data += 16;
                dr_data += 16;

                b_data += 16;
                g_data += 16;
                r_data += 16;
            }

            for(size_t i = span_width; i; --i) {
                *db_data++ = *b_data++;
            }

            for(size_t i = span_width; i; --i) {
                *dg_data++ = *g_data++;
            }

            for(size_t i = span_width; i; --i) {
                *dr_data++ = *r_data++;
            }

            b_data_l += width_;
            g_data_l += width_;
            r_data_l += width_;

            db_data_l += dw;
            dg_data_l += dw;
            dr_data_l += dw;
        }
    });
}

void SOASpriteRGB::blit_on_sprite_semitransparent(SOASpriteRGB& dsprite, size_t x, size_t y) {
    const size_t sw = width_;
    const size_t sh = height_;
    auto bbuf = b_buffer_;
    auto gbuf = g_buffer_;
    auto rbuf = r_buffer_;
    dsprite.lock([&](auto dw, auto dh, auto dr_buf, auto dg_buf, auto db_buf) {
        if(x >= dw || y >= dh) {
            return;
        }

        size_t span_width = dw - x;
        if(span_width > sw) {
            span_width = sw;
        }

        size_t span16_count = span_width / 16;
        span_width %= 16;

        size_t span_count = dh - y;
        if(span_count > sh) {
            span_count = sh;
        }

        uint8_t* b_data_l = &bbuf[0];
        uint8_t* g_data_l = &gbuf[0];
        uint8_t* r_data_l = &rbuf[0];

        uint8_t* db_data_l = &db_buf[x + dw * y];
        uint8_t* dg_data_l = &dg_buf[x + dw * y];
        uint8_t* dr_data_l = &dr_buf[x + dw * y];

        for(size_t j = span_count; j; --j) {
            uint8_t* b_data = b_data_l;
            uint8_t* g_data = g_data_l;
            uint8_t* r_data = r_data_l;

            uint8_t* db_data = db_data_l;
            uint8_t* dg_data = dg_data_l;
            uint8_t* dr_data = dr_data_l;

            for(size_t i = span16_count; i; --i) {
                __m128i half_b = _mm_avg_epu8(_mm_loadu_si128(reinterpret_cast<__m128i*>(db_data)), _mm_loadu_si128(reinterpret_cast<__m128i*>(b_data)));
                __m128i half_g = _mm_avg_epu8(_mm_loadu_si128(reinterpret_cast<__m128i*>(dg_data)), _mm_loadu_si128(reinterpret_cast<__m128i*>(g_data)));
                __m128i half_r = _mm_avg_epu8(_mm_loadu_si128(reinterpret_cast<__m128i*>(dr_data)), _mm_loadu_si128(reinterpret_cast<__m128i*>(r_data)));
                _mm_storeu_si128(reinterpret_cast<__m128i*>(db_data), half_b);
                _mm_storeu_si128(reinterpret_cast<__m128i*>(dg_data), half_g);
                _mm_storeu_si128(reinterpret_cast<__m128i*>(dr_data), half_r);
                db_data += 16;
                dg_data += 16;
                dr_data += 16;

                b_data += 16;
                g_data += 16;
                r_data += 16;
            }

            for(size_t i = span_width; i; --i) {
                *db_data = (*db_data + *b_data++) / 2;
                db_data++;
            }

            for(size_t i = span_width; i; --i) {
                *dg_data = (*dg_data + *g_data++) / 2;
                dg_data++;
            }

            for(size_t i = span_width; i; --i) {
                *dr_data = (*dr_data + *r_data++) / 2;
                dr_data++;
            }

            b_data_l += sw;
            g_data_l += sw;
            r_data_l += sw;

            db_data_l += dw;
            dg_data_l += dw;
            dr_data_l += dw;
        }
    });
}

void SOASpriteRGB::blit_on_sprite_colorkeyed(SOASpriteRGB& dsprite, size_t x, size_t y, uint8_t key_red, uint8_t key_green, uint8_t key_blue) {
    const size_t sw = width_;
    const size_t sh = height_;
    auto bbuf = b_buffer_;
    auto gbuf = g_buffer_;
    auto rbuf = r_buffer_;

    __m128i ckr = _mm_set1_epi8((int8_t)key_red);
    __m128i ckg = _mm_set1_epi8((int8_t)key_green);
    __m128i ckb = _mm_set1_epi8((int8_t)key_blue);

    dsprite.lock([&](auto dw, auto dh, auto dr_buf, auto dg_buf, auto db_buf) {
        if(x >= dw || y >= dh) {
            return;
        }

        size_t span_width = dw - x;
        if(span_width > sw) {
            span_width = sw;
        }

        size_t span16_count = span_width / 16;
        span_width %= 16;

        size_t span_count = dh - y;
        if(span_count > sh) {
            span_count = sh;
        }

        uint8_t* b_data_l = &bbuf[0];
        uint8_t* g_data_l = &gbuf[0];
        uint8_t* r_data_l = &rbuf[0];

        uint8_t* db_data_l = &db_buf[x + dw * y];
        uint8_t* dg_data_l = &dg_buf[x + dw * y];
        uint8_t* dr_data_l = &dr_buf[x + dw * y];

        for(size_t j = span_count; j; --j) {
            uint8_t* b_data = b_data_l;
            uint8_t* g_data = g_data_l;
            uint8_t* r_data = r_data_l;

            uint8_t* db_data = db_data_l;
            uint8_t* dg_data = dg_data_l;
            uint8_t* dr_data = dr_data_l;

            for(size_t i = span16_count; i; --i) {
                auto bbatch = _mm_loadu_si128(reinterpret_cast<__m128i*>(b_data));
                auto gbatch = _mm_loadu_si128(reinterpret_cast<__m128i*>(g_data));
                auto rbatch = _mm_loadu_si128(reinterpret_cast<__m128i*>(r_data));

                auto ckeyed = _mm_and_si128(
                    _mm_and_si128(
                        _mm_cmpeq_epi8(bbatch, ckb),
                        _mm_cmpeq_epi8(gbatch, ckg)
                    ),
                    _mm_cmpeq_epi8(rbatch, ckr)
                );

                __m128i res_b = _mm_or_si128(
                    _mm_andnot_si128(ckeyed, bbatch),
                    _mm_and_si128(ckeyed, _mm_loadu_si128(reinterpret_cast<__m128i*>(db_data)))
                );
                __m128i res_g = _mm_or_si128(
                    _mm_andnot_si128(ckeyed, gbatch),
                    _mm_and_si128(ckeyed, _mm_loadu_si128(reinterpret_cast<__m128i*>(dg_data)))
                );
                __m128i res_r = _mm_or_si128(
                    _mm_andnot_si128(ckeyed, rbatch),
                    _mm_and_si128(ckeyed, _mm_loadu_si128(reinterpret_cast<__m128i*>(dr_data)))
                );

                _mm_storeu_si128(reinterpret_cast<__m128i*>(db_data), res_b);
                _mm_storeu_si128(reinterpret_cast<__m128i*>(dg_data), res_g);
                _mm_storeu_si128(reinterpret_cast<__m128i*>(dr_data), res_r);

                db_data += 16;
                dg_data += 16;
                dr_data += 16;

                b_data += 16;
                g_data += 16;
                r_data += 16;
            }

            for(size_t i = span_width; i; --i) {
                auto ckeyed = ((*b_data & key_blue) & (*g_data & key_green) & (*r_data & key_red)) == 0;

                if(!ckeyed) {
                    *db_data = *b_data;
                    *dg_data = *g_data;
                    *dr_data = *r_data;
                }

                db_data++;
                dg_data++;
                dr_data++;

                b_data++;
                g_data++;
                r_data++;
            }

            b_data_l += sw;
            g_data_l += sw;
            r_data_l += sw;

            db_data_l += dw;
            dg_data_l += dw;
            dr_data_l += dw;
        }
    });
}

void SOASpriteRGB::blit_on_sprite_colorkeyed16(SOASpriteRGB& dsprite, size_t x, size_t y, uint8_t key_red, uint8_t key_green, uint8_t key_blue) {
    const size_t sw = width_;
    const size_t sh = height_;
    auto bbuf = b_buffer_;
    auto gbuf = g_buffer_;
    auto rbuf = r_buffer_;

    __m128i ckr = _mm_set1_epi8((int8_t)(key_red & 0xF0));
    __m128i ckg = _mm_set1_epi8((int8_t)(key_green & 0xF0));
    __m128i ckb = _mm_set1_epi8((int8_t)(key_blue & 0xF0));
    __m128i ckfilter = _mm_set1_epi8((int8_t)0xF0);

    dsprite.lock([&](auto dw, auto dh, auto dr_buf, auto dg_buf, auto db_buf) {
        if(x >= dw || y >= dh) {
            return;
        }

        size_t span_width = dw - x;
        if(span_width > sw) {
            span_width = sw;
        }

        size_t span16_count = span_width / 16;
        span_width %= 16;

        size_t span_count = dh - y;
        if(span_count > sh) {
            span_count = sh;
        }

        uint8_t* b_data_l = &bbuf[0];
        uint8_t* g_data_l = &gbuf[0];
        uint8_t* r_data_l = &rbuf[0];

        uint8_t* db_data_l = &db_buf[x + dw * y];
        uint8_t* dg_data_l = &dg_buf[x + dw * y];
        uint8_t* dr_data_l = &dr_buf[x + dw * y];

        for(size_t j = span_count; j; --j) {
            uint8_t* b_data = b_data_l;
            uint8_t* g_data = g_data_l;
            uint8_t* r_data = r_data_l;

            uint8_t* db_data = db_data_l;
            uint8_t* dg_data = dg_data_l;
            uint8_t* dr_data = dr_data_l;

            for(size_t i = span16_count; i; --i) {
                auto bbatch = _mm_loadu_si128(reinterpret_cast<__m128i*>(b_data));
                auto gbatch = _mm_loadu_si128(reinterpret_cast<__m128i*>(g_data));
                auto rbatch = _mm_loadu_si128(reinterpret_cast<__m128i*>(r_data));

                auto ckeyed = _mm_and_si128(
                    _mm_and_si128(
                        _mm_cmpeq_epi8(_mm_and_si128(bbatch, ckfilter), ckb),
                        _mm_cmpeq_epi8(_mm_and_si128(gbatch, ckfilter), ckg)
                    ),
                    _mm_cmpeq_epi8(_mm_and_si128(rbatch, ckfilter), ckr)
                );

                __m128i res_b = _mm_or_si128(
                    _mm_andnot_si128(ckeyed, bbatch),
                    _mm_and_si128(ckeyed, _mm_loadu_si128(reinterpret_cast<__m128i*>(db_data)))
                );
                __m128i res_g = _mm_or_si128(
                    _mm_andnot_si128(ckeyed, gbatch),
                    _mm_and_si128(ckeyed, _mm_loadu_si128(reinterpret_cast<__m128i*>(dg_data)))
                );
                __m128i res_r = _mm_or_si128(
                    _mm_andnot_si128(ckeyed, rbatch),
                    _mm_and_si128(ckeyed, _mm_loadu_si128(reinterpret_cast<__m128i*>(dr_data)))
                );

                _mm_storeu_si128(reinterpret_cast<__m128i*>(db_data), res_b);
                _mm_storeu_si128(reinterpret_cast<__m128i*>(dg_data), res_g);
                _mm_storeu_si128(reinterpret_cast<__m128i*>(dr_data), res_r);

                db_data += 16;
                dg_data += 16;
                dr_data += 16;

                b_data += 16;
                g_data += 16;
                r_data += 16;
            }

            for(size_t i = span_width; i; --i) {
                auto ckeyed = (((*b_data & 0xF0) == key_blue) && ((*g_data & 0xF0) == key_green) && ((*r_data & 0xF0) == key_red));

                if(!ckeyed) {
                    *db_data = *b_data;
                    *dg_data = *g_data;
                    *dr_data = *r_data;
                }

                db_data++;
                dg_data++;
                dr_data++;

                b_data++;
                g_data++;
                r_data++;
            }

            b_data_l += sw;
            g_data_l += sw;
            r_data_l += sw;

            db_data_l += dw;
            dg_data_l += dw;
            dr_data_l += dw;
        }
    });
}
