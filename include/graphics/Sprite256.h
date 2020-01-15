#ifndef SPRITE_256_H__
#define SPRITE_256_H__

#include <inttypes.h>
#include <stddef.h>
#include <loaders/ksy/rage_of_mages_1_256.h>

struct SOASpriteRGB;

struct Sprite256
{
    Sprite256(rage_of_mages_1_256_t* data);
    Sprite256(const Sprite256&) = delete;
    Sprite256& operator=(const Sprite256&) = delete;
    Sprite256(Sprite256&&) = delete;
    Sprite256& operator=(Sprite256&&) = delete;
    ~Sprite256();
    void blit_on_sprite_centered(SOASpriteRGB& other, int32_t x, int32_t y, uint16_t frame_number, int32_t off_x, int32_t off_y, int32_t fixed_w, int32_t fixed_h);
    void blit_on_sprite(SOASpriteRGB& other, int32_t x, int32_t y, uint16_t frame_number);
    void blit_shadow_centered(SOASpriteRGB& other,
        int32_t x, int32_t y,
        uint16_t frame_number,
        int32_t off_x,
        int32_t off_y,
        int32_t fixed_w,
        int32_t fixed_h,
        uint16_t bottom_y,
        uint8_t y_scale,
        int32_t shift_amount
    );
    void blit_shadow(SOASpriteRGB& other,
        int32_t x, int32_t y,
        uint16_t frame_number,
        uint16_t bottom_y, uint8_t y_scale,
        int32_t shift_amount
    );
    uint16_t frame_count() const;
private:
    uint8_t palette_r_[256];
    uint8_t palette_g_[256];
    uint8_t palette_b_[256];
    uint16_t frame_count_;
    std::vector<std::tuple<uint32_t, uint16_t, uint16_t, uint16_t>> frame_info_vector_;
    uint8_t* buffer_raw_;
};

#endif /* end of include guard: SPRITE_256_H__ */
