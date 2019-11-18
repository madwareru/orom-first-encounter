#ifndef PNGLOADER_H
#define PNGLOADER_H

#include "soaspritergb.h"
#include "soapritergba.h"
#include <memory>

std::shared_ptr<SOASpriteRGB> load_sprite_from_png_24(const char* filename);
std::shared_ptr<SOASpriteRGBA> load_sprite_from_png_32(const char* filename);

template<typename T> std::shared_ptr<T> load_sprite_from_png(const char* filename) {
#define IF_MATCH(x) if constexpr (std::is_same_v<T, x>)
#define EL_IF_MATCH(x) else IF_MATCH(x)

    IF_MATCH(SOASpriteRGB) return load_sprite_from_png_24(filename);
    EL_IF_MATCH(SOASpriteRGBA) return load_sprite_from_png_32(filename);
    else return std::make_shared<T>(1, 1);

#undef EL_IF_MATCH
#undef IF_MATCH
}

#endif // PNGLOADER_H
