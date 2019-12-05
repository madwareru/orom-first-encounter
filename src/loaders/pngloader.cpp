#include <graphics/soaspritergb.h>
#include <graphics/soaspritergba.h>
#include <loaders/pngloader.h>
#include <util/defer_action.h>
#include "../../third_party/lodepng.h"
#include <cinttypes>
#include <iostream>

std::shared_ptr<SOASpriteRGB> load_sprite_from_png_24(std::string& memory_buffer) {
    uint8_t* image_bytes = nullptr;
    uint32_t lodepng_w, lodepng_h;

    const char* in_bytes = memory_buffer.c_str();
    uint8_t* in_bytes_copy = new uint8_t[memory_buffer.size()];
    memcpy((void*)in_bytes_copy, (void*)in_bytes, memory_buffer.size());
    DEFER([&in_bytes_copy]() {delete [] in_bytes_copy; });

    const auto lodepng_err = lodepng_decode24(
        &image_bytes,
        &lodepng_w,
        &lodepng_h,
        in_bytes_copy,
        memory_buffer.size()
    );
    DEFER([&image_bytes]()
    {
        if (image_bytes != nullptr) {
            free(reinterpret_cast<void*>(image_bytes));
        }
    })

    if(lodepng_err != 0) {
        std::cerr << "error " << lodepng_err << ": " << lodepng_error_text(lodepng_err) << std::endl;
        return std::make_shared<SOASpriteRGB>(1,1);
    }

    auto result = std::make_shared<SOASpriteRGB>(lodepng_w, lodepng_h);
    result->lock([image_bytes](auto dw, auto dh, auto r_buf, auto g_buf, auto b_buf){
        uint8_t* p = image_bytes;
        for(size_t j = 0; j < dh; ++j){
            for(size_t i = 0; i < dw; ++i){
                *r_buf++= *p++;
                *g_buf++= *p++;
                *b_buf++= *p++;
            }
        }
    });
    return result;
}

std::shared_ptr<SOASpriteRGB> load_sprite_from_png_24(const char* filename) {
    uint8_t* image_bytes = nullptr;
    uint32_t lodepng_w, lodepng_h;

    const auto lodepng_err = lodepng_decode24_file(&image_bytes, &lodepng_w, &lodepng_h, filename);
    DEFER([&image_bytes]()
    {
        if (image_bytes != nullptr) {
            free(reinterpret_cast<void*>(image_bytes));
        }        
    })

    if(lodepng_err != 0) {
        std::cerr << "error " << lodepng_err << ": " << lodepng_error_text(lodepng_err) << std::endl;
        return std::make_shared<SOASpriteRGB>(1,1);
    }

    auto result = std::make_shared<SOASpriteRGB>(lodepng_w, lodepng_h);
    result->lock([image_bytes](auto dw, auto dh, auto r_buf, auto g_buf, auto b_buf){
        uint8_t* p = image_bytes;
        for(size_t j = 0; j < dh; ++j){
            for(size_t i = 0; i < dw; ++i){
                *r_buf++= *p++;
                *g_buf++= *p++;
                *b_buf++= *p++;
            }
        }
    });
    return result;
}

std::shared_ptr<SOASpriteRGBA> load_sprite_from_png_32(const char* filename) {
    uint8_t* image_bytes = nullptr;
    uint32_t lodepng_w, lodepng_h;

    const auto lodepng_err = lodepng_decode32_file(&image_bytes, &lodepng_w, &lodepng_h, filename);
    DEFER([&image_bytes]()
    {
        if (image_bytes != nullptr) {
            free(reinterpret_cast<void*>(image_bytes));
        }
    })

    if(lodepng_err != 0) {
        std::cerr << "error " << lodepng_err << ": " << lodepng_error_text(lodepng_err) << std::endl;
        return std::make_shared<SOASpriteRGBA>(1,1);
    }

    auto result = std::make_shared<SOASpriteRGBA>(lodepng_w, lodepng_h);
    result->lock([image_bytes](auto dw, auto dh, auto r_buf, auto g_buf, auto b_buf, auto a_buf){
        uint8_t* p = image_bytes;
        for(size_t j = 0; j < dh; ++j){
            for(size_t i = 0; i < dw; ++i){
                *r_buf++= *p++;
                *g_buf++= *p++;
                *b_buf++= *p++;
                *a_buf++= *p++;
            }
        }
    });
    return result;
}
