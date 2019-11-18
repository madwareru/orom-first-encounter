#ifndef SOASPRITERGB_H
#define SOASPRITERGB_H

#include <cinttypes>
#include <Windows.h>
#include <wingdi.h>

struct FrameBuffer;
struct SOASpriteRGB;

struct SOASpriteRGB {
    SOASpriteRGB(size_t w, size_t h);
    SOASpriteRGB(const SOASpriteRGB& other) = delete;
    SOASpriteRGB& operator=(const SOASpriteRGB&) = delete;
    SOASpriteRGB(SOASpriteRGB&& other) = delete;
    SOASpriteRGB& operator=(SOASpriteRGB&&) = delete;
    ~SOASpriteRGB();
    void blit_on_sprite(SOASpriteRGB& other, size_t x, size_t y);
    void blit_on_sprite_colorkeyed(SOASpriteRGB& other, size_t x, size_t y, uint8_t key_red, uint8_t key_green, uint8_t key_blue);
    void blit_on_sprite_colorkeyed16(SOASpriteRGB& other, size_t x, size_t y, uint8_t key_red, uint8_t key_green, uint8_t key_blue);
    void blit_on_sprite_semitransparent(SOASpriteRGB& other, size_t x, size_t y);
    void blit_on_frame_buffer(FrameBuffer& other, size_t x, size_t y);
    template<typename FF>
    void mutate(FF&& predicate) {
        predicate(width_, height_, r_buffer_, g_buffer_, b_buffer_);
    }
private:
    size_t width_;
    size_t height_;

    uint8_t* r_buffer_raw_;
    uint8_t* g_buffer_raw_;
    uint8_t* b_buffer_raw_;

    uint8_t* r_buffer_;
    uint8_t* g_buffer_;
    uint8_t* b_buffer_;
};

#endif // SOASPRITERGB_H
