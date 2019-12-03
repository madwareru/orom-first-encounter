#ifndef SPRITE_16A_H_
#define SPRITE_16A_H_

#include <cinttypes>
#include <loaders/ksy/rage_of_mages_1_16a.h>

struct SOASpriteRGB;

struct Sprite16a
{
    Sprite16a(rage_of_mages_1_16a_t* data);
    Sprite16a(const Sprite16a&) = delete;
    Sprite16a& operator=(const Sprite16a&) = delete;
    Sprite16a(Sprite16a&&) = delete;
    Sprite16a& operator=(Sprite16a&&) = delete;
    ~Sprite16a();
    void blit_on_sprite(SOASpriteRGB& other, int32_t x, int32_t y, uint16_t frame_number);
    uint16_t frame_count() const;
private:
    uint8_t palette_r_[256];
    uint8_t palette_g_[256];
    uint8_t palette_b_[256];
    uint16_t frame_count_;
    std::vector<std::tuple<uint16_t, uint16_t, uint16_t, uint16_t>> frame_info_vector_;
    uint8_t* buffer_raw_;
};

#endif /* end of include guard: SPRITE_16A_H_ */
