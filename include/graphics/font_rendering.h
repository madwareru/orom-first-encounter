#ifndef FONT_RENDERER_H
#define FONT_RENDERER_H

#include <vector>
#include <memory>

struct Sprite16;
struct ResourceFile;

struct Font16 {
    Font16(std::shared_ptr<Sprite16> sprite, std::vector<uint16_t>&& glyph_width_storage);
    Font16(std::shared_ptr<ResourceFile> graphic_resources, const char* sprite_path, const char* gliph_data_path);
    Font16(const Font16&) = delete;
    Font16& operator=(const Font16&) = delete;
    Font16(Font16&&) = delete;
    Font16& operator=(Font16&&) = delete;
    void render_text(const std::string& text_to_render, int16_t x, int16_t y);
private:
    std::shared_ptr<Sprite16> font_sprite_;
    std::vector<uint16_t> glyph_width_storage_;
};

#endif /* end of include guard: FONT_RENDERER_H */
