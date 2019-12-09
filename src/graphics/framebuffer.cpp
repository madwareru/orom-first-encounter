#include <util/macro_shared.h>
#include <graphics/framebuffer.h>
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
    bitmap_info_.bmiHeader.biCompression = BI_RGB; // Uncompressed
    bitmap_info_.bmiHeader.biXPelsPerMeter = 0; // used by biCompression so ignored
    bitmap_info_.bmiHeader.biYPelsPerMeter = 0; // used by biCompression so ignored
    bitmap_info_.bmiHeader.biClrUsed = 0; // we don't have a color tale so it should be zero
    bitmap_info_.bmiHeader.biClrImportant = 0; // we require all colors so it should be zero

    for(size_t i = 0; i < w * h; ++i) {
        color_buffer_[i] = 0;
    }
}

FrameBuffer::~FrameBuffer() {
    delete [] raw_buffer_;
}

void FrameBuffer::blit_on_dc(const HDC& hdc) {
    auto scan_lines_set = SetDIBitsToDevice(
        hdc, 0, 0,
        static_cast<uint32_t>(width_),
        static_cast<uint32_t>(height_),
        0, 0, 0,
        static_cast<uint32_t>(height_),
        &color_buffer_[0],
        &bitmap_info_, 0);
    LOG_ASSERT(scan_lines_set != 0)
}
