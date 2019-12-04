#include <graphics/font_rendering.h>
#include <util/macro_shared.h>

#include <loaders/resource_file.h>
#include <graphics/soaspritergb.h>
#include <graphics/Sprite16.h>
#include <graphics/Sprite16a.h>

static uint8_t symbol_to_font_atlas_lookup[256] = {
    REPEAT_32(0),         // [0x00..0x20) <- missing
    //--------------------------------------------------------------------------------
    ROW_64_ASCENDING(0),  // [0x20..0x60)                                 < LATIN
    ROW_32_ASCENDING(64), // [0x60..0x80)                                 < PART
    //--------------------------------------------------------------------------------
    REPEAT_32(0),         // [0x80..0xA0) various special symbols ignored
    //--------------------------------------------------------------------------------
    REPEAT_8(0),  112, 0, 0, 0, REPEAT_4(0), // [0xA0..0xB0) Ё
    REPEAT_8(0),  105, 0, 0, 0, REPEAT_4(0), // [0xB0..0xC0) ё
    ROW_32_ASCENDING(0x90), // [0xC0..0xE0)                               <  CYRILLIC
    ROW_16_ASCENDING(0xB0), // [0xE0..0xF0)                               <  PART
    ROW_16_ASCENDING(0xD0)  // [0xF0..0xFF]
};

Font16::Font16(std::shared_ptr<Sprite16> sprite, std::vector<uint16_t>&& glyph_width_storage)
    :
    font_sprite_{sprite},
    glyph_width_storage_{glyph_width_storage}
    {}

Font16a::Font16a(std::shared_ptr<Sprite16a> sprite, std::vector<uint16_t>&& glyph_width_storage)
    :
    font_sprite_{sprite},
    glyph_width_storage_{glyph_width_storage}
    {}

void Font16::render_text(const std::string &text_to_render, SOASpriteRGB &other, int16_t x, int16_t y) {
    int16_t current_x = x;
    int16_t current_y = y;
    const size_t stroke_height = 18; //todo: make it tweakable from an asset
    const size_t kerning = 2;
    std::shared_ptr<Sprite16> last_sprite;
    for(size_t i = 0; i < text_to_render.size(); ++i) {
        char current_char = text_to_render[i];
        if(current_char == '\n') {
            current_y += stroke_height;
            current_x = x;
            continue;
        } else if(current_char == ' ') {
            current_x += 4;
            continue;
        }
        const uint8_t mapped = symbol_to_font_atlas_lookup[(current_char + 0x100) & 0xFF];

        if(mapped == 0) {
            continue;
        }

        if(mapped >= font_sprite_->frame_count()) {
            continue;
        }

        if(mapped >= glyph_width_storage_.size()) {
            continue;
        }

        const uint16_t current_glyph_width = glyph_width_storage_[mapped];

        if(current_x < static_cast<int16_t>(other.width()) && current_y < static_cast<int16_t>(other.height())) {
            font_sprite_->blit_on_sprite(other, current_x, current_y, mapped);
        }

        current_x += current_glyph_width + kerning;
    }
}

void Font16::render_text(const char* text_to_render, SOASpriteRGB &other, int16_t x, int16_t y) {
    int32_t current_x = x;
    int32_t current_y = y;
    const size_t stroke_height = 18; //todo: make it tweakable from an asset
    const size_t kerning = 2;
    std::shared_ptr<Sprite16> last_sprite;
    for(size_t i = 0; text_to_render[i] != '\0'; ++i) {
        char current_char = text_to_render[i];
        if(current_char == '\n') {
            current_y += stroke_height;
            current_x = x;
            continue;
        } else if(current_char == ' ') {
            current_x += 4;
            continue;
        }
        const uint8_t mapped = symbol_to_font_atlas_lookup[(current_char + 0x100) & 0xFF];
        if(mapped == 0) {
            continue;
        }

        if(mapped >= font_sprite_->frame_count()) {
            continue;
        }

        if(mapped >= glyph_width_storage_.size()) {
            continue;
        }

        const uint16_t current_glyph_width = glyph_width_storage_[mapped];

        if(current_x < static_cast<int16_t>(other.width()) && current_y < static_cast<int16_t>(other.height())) {
            font_sprite_->blit_on_sprite(other, current_x, current_y, mapped);
        }

        current_x += current_glyph_width + kerning;
    }
}

void Font16a::render_text(const std::string &text_to_render, SOASpriteRGB &other, int16_t x, int16_t y) {
    int16_t current_x = x;
    int16_t current_y = y;
    const size_t stroke_height = 18; //todo: make it tweakable from an asset
    const size_t kerning = 2;
    std::shared_ptr<Sprite16> last_sprite;
    for(size_t i = 0; i < text_to_render.size(); ++i) {
        char current_char = text_to_render[i];
        if(current_char == '\n') {
            current_y += stroke_height;
            current_x = x;
            continue;
        } else if(current_char == ' ') {
            current_x += 4;
            continue;
        }
        const uint8_t mapped = symbol_to_font_atlas_lookup[(current_char + 0x100) & 0xFF];

        if(mapped == 0) {
            continue;
        }

        if(mapped >= font_sprite_->frame_count()) {
            continue;
        }

        if(mapped >= glyph_width_storage_.size()) {
            continue;
        }

        const uint16_t current_glyph_width = glyph_width_storage_[mapped];

        if(current_x < static_cast<int16_t>(other.width()) && current_y < static_cast<int16_t>(other.height())) {
            font_sprite_->blit_on_sprite(other, current_x, current_y, mapped);
        }

        current_x += current_glyph_width + kerning;
    }
}

void Font16a::render_text(const char* text_to_render, SOASpriteRGB &other, int16_t x, int16_t y) {
    int32_t current_x = x;
    int32_t current_y = y;
    const size_t stroke_height = 18; //todo: make it tweakable from an asset
    const size_t kerning = 2;
    std::shared_ptr<Sprite16> last_sprite;
    for(size_t i = 0; text_to_render[i] != '\0'; ++i) {
        char current_char = text_to_render[i];
        if(current_char == '\n') {
            current_y += stroke_height;
            current_x = x;
            continue;
        } else if(current_char == ' ') {
            current_x += 4;
            continue;
        }
        const uint8_t mapped = symbol_to_font_atlas_lookup[(current_char + 0x100) & 0xFF];
        if(mapped == 0) {
            continue;
        }

        if(mapped >= font_sprite_->frame_count()) {
            continue;
        }

        if(mapped >= glyph_width_storage_.size()) {
            continue;
        }

        const uint16_t current_glyph_width = glyph_width_storage_[mapped];

        if(current_x < static_cast<int16_t>(other.width()) && current_y < static_cast<int16_t>(other.height())) {
            font_sprite_->blit_on_sprite(other, current_x, current_y, mapped);
        }

        current_x += current_glyph_width + kerning;
    }
}
