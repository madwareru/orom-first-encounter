#ifndef FONT_RENDERER_H
#define FONT_RENDERER_H

#include <vector>
#include <memory>

struct Sprite16;
struct Sprite16a;
struct SOASpriteRGB;
struct ResourceFile;

struct Font16 {
    Font16(std::shared_ptr<Sprite16> sprite, std::vector<uint16_t>&& glyph_width_storage);
    Font16(const Font16&) = delete;
    Font16& operator=(const Font16&) = delete;
    Font16(Font16&&) = delete;
    Font16& operator=(Font16&&) = delete;
    void render_text(const char* text_to_render, SOASpriteRGB &other, int16_t x, int16_t y);
    void render_text(const std::string& text_to_render, SOASpriteRGB& other, int16_t x, int16_t y);
    void render_text(const char* text_to_render, SOASpriteRGB &other, int16_t x, int16_t y, uint8_t palette_id);
    void render_text(const std::string& text_to_render, SOASpriteRGB& other, int16_t x, int16_t y, uint8_t palette_id);
private:
    std::shared_ptr<Sprite16> font_sprite_;
    std::vector<uint16_t> glyph_width_storage_;
};

struct Font16a {
    Font16a(std::shared_ptr<Sprite16a> sprite, std::vector<uint16_t>&& glyph_width_storage);
    Font16a(const Font16a&) = delete;
    Font16a& operator=(const Font16a&) = delete;
    Font16a(Font16&&) = delete;
    Font16a& operator=(Font16a&&) = delete;
    void render_text(const char* text_to_render, SOASpriteRGB &other, int16_t x, int16_t y);
    void render_text(const std::string& text_to_render, SOASpriteRGB& other, int16_t x, int16_t y);
private:
    std::shared_ptr<Sprite16a> font_sprite_;
    std::vector<uint16_t> glyph_width_storage_;
};

#endif /* end of include guard: FONT_RENDERER_H */
