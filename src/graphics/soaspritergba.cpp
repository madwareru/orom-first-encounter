#include <graphics/soaspritergba.h>
#include <emmintrin.h>
#include <iostream>

SOASpriteRGBA::SOASpriteRGBA(size_t w, size_t h): width_{w}, height_{h} {
    r_buffer_raw_ = new uint8_t[w * h + 8];
    g_buffer_raw_ = new uint8_t[w * h + 8];
    b_buffer_raw_ = new uint8_t[w * h + 8];
    a_buffer_raw_ = new uint8_t[w * h + 8];

    r_buffer_ = (reinterpret_cast<int32_t>(&r_buffer_raw_[0]) % 16 == 0)
        ? &r_buffer_raw_[0]
        : &r_buffer_raw_[8];

    g_buffer_ = (reinterpret_cast<int32_t>(&g_buffer_raw_[0]) % 16 == 0)
        ? &g_buffer_raw_[0]
        : &g_buffer_raw_[8];

    b_buffer_ = (reinterpret_cast<int32_t>(&b_buffer_raw_[0]) % 16 == 0)
        ? &b_buffer_raw_[0]
        : &b_buffer_raw_[8];

    a_buffer_ = (reinterpret_cast<int32_t>(&a_buffer_raw_[0]) % 16 == 0)
        ? &a_buffer_raw_[0]
        : &a_buffer_raw_[8];
}

SOASpriteRGBA::~SOASpriteRGBA(){
    delete [] a_buffer_raw_;
    delete [] b_buffer_raw_;
    delete [] g_buffer_raw_;
    delete [] r_buffer_raw_;
}

void SOASpriteRGBA::blit_on_sprite(SOASpriteRGB& dsprite, size_t x, size_t y) {
    const size_t sw = width_;
    const size_t sh = height_;
    auto abuf = a_buffer_;
    auto bbuf = b_buffer_;
    auto gbuf = g_buffer_;
    auto rbuf = r_buffer_;
    dsprite.mutate([&](auto dw, auto dh, auto dr_buf, auto dg_buf, auto db_buf) {
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

        uint8_t* a_data_l = &abuf[0];
        uint8_t* b_data_l = &bbuf[0];
        uint8_t* g_data_l = &gbuf[0];
        uint8_t* r_data_l = &rbuf[0];

        uint8_t* db_data_l = &db_buf[x + dw * y];
        uint8_t* dg_data_l = &dg_buf[x + dw * y];
        uint8_t* dr_data_l = &dr_buf[x + dw * y];

        auto m_z = _mm_set1_epi32(0);

        for(size_t j = span_count; j; --j) {
            uint8_t* a_data = a_data_l;
            uint8_t* b_data = b_data_l;
            uint8_t* g_data = g_data_l;
            uint8_t* r_data = r_data_l;

            uint8_t* db_data = db_data_l;
            uint8_t* dg_data = dg_data_l;
            uint8_t* dr_data = dr_data_l;

            for(size_t i = span16_count; i; --i) {
                auto ad = _mm_loadu_si128(reinterpret_cast<__m128i*>(a_data));
                auto bd = _mm_loadu_si128(reinterpret_cast<__m128i*>(b_data));
                auto gd = _mm_loadu_si128(reinterpret_cast<__m128i*>(g_data));
                auto rd = _mm_loadu_si128(reinterpret_cast<__m128i*>(r_data));

                auto dbd = _mm_loadu_si128(reinterpret_cast<__m128i*>(db_data));
                auto dgd = _mm_loadu_si128(reinterpret_cast<__m128i*>(dg_data));
                auto drd = _mm_loadu_si128(reinterpret_cast<__m128i*>(dr_data));

                // prepare data by unpacking and interlieving

                auto m_a_lo = _mm_unpacklo_epi8(ad, m_z);
                auto m_a_hi = _mm_unpackhi_epi8(ad, m_z);

                auto m_b_lo = _mm_unpacklo_epi8(bd, m_z);
                auto m_b_hi = _mm_unpackhi_epi8(bd, m_z);

                auto m_g_lo = _mm_unpacklo_epi8(gd, m_z);
                auto m_g_hi = _mm_unpackhi_epi8(gd, m_z);

                auto m_r_lo = _mm_unpacklo_epi8(rd, m_z);
                auto m_r_hi = _mm_unpackhi_epi8(rd, m_z);

                auto m_db_lo = _mm_unpacklo_epi8(dbd, m_z);
                auto m_db_hi = _mm_unpackhi_epi8(dbd, m_z);

                auto m_dg_lo = _mm_unpacklo_epi8(dgd, m_z);
                auto m_dg_hi = _mm_unpackhi_epi8(dgd, m_z);

                auto m_dr_lo = _mm_unpacklo_epi8(drd, m_z);
                auto m_dr_hi = _mm_unpackhi_epi8(drd, m_z);

                // calculating diffs:

                #define DIFFR(x, lohi) \
                    auto df_##x##_##lohi = _mm_sub_epi16(m_##x##_##lohi, m_d##x##_##lohi)
                #define DIFF_COMP(x) DIFFR(x, lo); DIFFR(x, hi)
                    DIFF_COMP(b);
                    DIFF_COMP(g);
                    DIFF_COMP(r);
                #undef DIFF_COMP
                #undef DIFFR

                // accs:

                #define ACC(x, lohi) \
                    auto acc_##x##_##lohi = _mm_mullo_epi16(df_##x##_##lohi, m_a_##lohi)
                #define ACC_COMP(x) ACC(x, lo); ACC(x, hi)
                    ACC_COMP(b);
                    ACC_COMP(g);
                    ACC_COMP(r);
                #undef ACC_COMP
                #undef ACC

                // adds:

                #define ADD_ACC(x, lohi) \
                    auto add_##x##_##lohi = \
                    _mm_srli_epi16(_mm_add_epi16(_mm_slli_epi16(m_d##x##_##lohi, 8), acc_##x##_##lohi), 8)
                #define ADD_ACC_COMP(x) ADD_ACC(x, lo); ADD_ACC(x, hi)
                    ADD_ACC_COMP(b);
                    ADD_ACC_COMP(g);
                    ADD_ACC_COMP(r);
                #undef ADD_ACC_COMP
                #undef ADD_ACC

                // finals:

                _mm_storeu_si128(reinterpret_cast<__m128i*>(db_data), _mm_packus_epi16(add_b_lo, add_b_hi));
                _mm_storeu_si128(reinterpret_cast<__m128i*>(dg_data), _mm_packus_epi16(add_g_lo, add_g_hi));
                _mm_storeu_si128(reinterpret_cast<__m128i*>(dr_data), _mm_packus_epi16(add_r_lo, add_r_hi));

                a_data += 16;
                b_data += 16;
                g_data += 16;
                r_data += 16;

                db_data += 16;
                dg_data += 16;
                dr_data += 16;
            }

            for(size_t i = span_width; i; --i) {
                auto alpha = *a_data++;

                *db_data = (*db_data * (255 - alpha) + *b_data++ * alpha) / 256;
                *dg_data = (*dg_data * (255 - alpha) + *g_data++ * alpha) / 256;
                *dr_data = (*dr_data * (255 - alpha) + *r_data++ * alpha) / 256;

                db_data++;
                dg_data++;
                dr_data++;
            }

            a_data_l += sw;
            b_data_l += sw;
            g_data_l += sw;
            r_data_l += sw;

            db_data_l += dw;
            dg_data_l += dw;
            dr_data_l += dw;
        }
    });
}

void SOASpriteRGBA::blit_on_sprite(SOASpriteRGB& dsprite, size_t dx, size_t dy, size_t sx, size_t sy, size_t w, size_t h) {
    const size_t sw = (sx + w > width_) ? width_ - sx : w;
    const size_t sh = (sy + h > height_) ? height_ - sy : h;
    auto abuf = a_buffer_;
    auto bbuf = b_buffer_;
    auto gbuf = g_buffer_;
    auto rbuf = r_buffer_;
    dsprite.mutate([&](auto dw, auto dh, auto dr_buf, auto dg_buf, auto db_buf) {

    });
}
