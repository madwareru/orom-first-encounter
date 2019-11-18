#include "framebuffer.h"
#include <intrin.h>

FrameBuffer::FrameBuffer(size_t w, size_t h): width_{w}, height_{h} {
    raw_buffer_ = new uint32_t[w * h + 2];

    color_buffer_ = (reinterpret_cast<int32_t>(&raw_buffer_[0]) % 16 == 0)
        ? &raw_buffer_[0]
        : &raw_buffer_[2];

    bitmap_info_.bmiHeader.biBitCount = 32;
    bitmap_info_.bmiHeader.biPlanes = 1;
    bitmap_info_.bmiHeader.biSize = sizeof(bitmap_info_.bmiHeader);
    bitmap_info_.bmiHeader.biWidth = static_cast<int32_t>(w);
    bitmap_info_.bmiHeader.biHeight = -static_cast<int32_t>(h);
    bitmap_info_.bmiHeader.biSizeImage = static_cast<uint32_t>(4 * w * h);
}

FrameBuffer::~FrameBuffer() {
    delete [] raw_buffer_;
}

void FrameBuffer::blit_on_dc(const HDC& hdc) {
    SetDIBitsToDevice(
        hdc, 0, 0,
        static_cast<uint32_t>(width_),
        static_cast<uint32_t>(height_),
        0, 0, 0,
        static_cast<uint32_t>(height_),
        &color_buffer_[0],
        &bitmap_info_, 0);

}
