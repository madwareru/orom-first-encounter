#ifndef SPRITE_16_H_
#define SPRITE_16_H_

#include <cinttypes>
#include <vector>
#include <tuple>
#include <loaders/ksy/rage_of_mages_1_16.h>

struct SOASpriteRGB;

struct Sprite16 {
    Sprite16(rage_of_mages_1_16_t* data);
    Sprite16(const Sprite16&) = delete;
    Sprite16& operator=(const Sprite16&) = delete;
    Sprite16(Sprite16&&) = delete;
    Sprite16& operator=(Sprite16&&) = delete;
    ~Sprite16();
    void blit_on_sprite(SOASpriteRGB& other, int32_t x, int32_t y, uint16_t frame_number);
    void blit_on_sprite(SOASpriteRGB& other, int32_t x, int32_t y, uint16_t frame_number, uint8_t palette_id);
    uint16_t frame_count() const;
private:
    uint16_t frame_count_;
    std::vector<std::tuple<uint16_t, uint16_t, uint16_t, uint16_t>> frame_info_vector_;
    uint8_t* buffer_raw_;
};

#endif /* end of include guard: SPRITE_16A_H_ */
