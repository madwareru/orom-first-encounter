#ifndef SOASPRITERGBA_H
#define SOASPRITERGBA_H

#include <cinttypes>

struct SOASpriteRGB;

struct SOASpriteRGBA
{
    SOASpriteRGBA(size_t w, size_t h);
    SOASpriteRGBA(const SOASpriteRGBA&) = delete;
    SOASpriteRGBA& operator=(const SOASpriteRGBA&) = delete;
    SOASpriteRGBA(SOASpriteRGBA&&) = delete;
    SOASpriteRGBA& operator=(SOASpriteRGBA&&) = delete;
    ~SOASpriteRGBA();
    void blit_on_sprite(SOASpriteRGB& other, int16_t x, int16_t y);
    void blit_on_sprite(SOASpriteRGB& other, size_t dx, size_t dy, size_t sx, size_t sy, size_t w, size_t h);
    template<typename FF>
    void lock(FF&& predicate) {
        predicate(width_, height_, r_buffer_, g_buffer_, b_buffer_, a_buffer_);
    }
    size_t width() const;
    size_t height() const;
private:
    size_t width_;
    size_t height_;

    uint8_t* r_buffer_raw_;
    uint8_t* g_buffer_raw_;
    uint8_t* b_buffer_raw_;
    uint8_t* a_buffer_raw_;

    uint8_t* r_buffer_;
    uint8_t* g_buffer_;
    uint8_t* b_buffer_;
    uint8_t* a_buffer_;
};

#endif

