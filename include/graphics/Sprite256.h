#ifndef SPRITE_256_H__
#define SPRITE_256_H__

#include <cinttypes>
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
    void blit_on_sprite(SOASpriteRGB& other, int32_t x, int32_t y, uint16_t frame_number);
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
