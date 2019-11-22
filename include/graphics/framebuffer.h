#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cinttypes>
#include <Windows.h>
#include <wingdi.h>

struct FrameBuffer;
struct SOASpriteRGB;

struct FrameBuffer {
    FrameBuffer(size_t w, size_t h);
    FrameBuffer(const FrameBuffer& other) = delete;
    FrameBuffer(FrameBuffer&& other) = delete;
    ~FrameBuffer();
    void blit_on_dc(const HDC& hdc);
    template<typename FF>
    void mutate(FF&& predicate) {
        predicate(width_, height_, color_buffer_);
    }
private:
    size_t width_;
    size_t height_;
    uint32_t* raw_buffer_;
    uint32_t* color_buffer_;
    BITMAPINFO bitmap_info_;
};

#endif // FRAMEBUFFER_H
