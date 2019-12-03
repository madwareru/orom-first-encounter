#include <graphics/font_renderer.h>
#include <util/macro_shared.h>

static uint8_t symbol_to_font_atlas_lookup[256] = {
    REPEAT_32(0),         // [0x00..0x20) <- missing
    //--------------------------------------------------------------------------------
    ROW_64_ASCENDING(0),  // [0x20..0x60)                                 < LATIN
    ROW_32_ASCENDING(64), // [0x60..0x80)                                 < PART
    //--------------------------------------------------------------------------------
    REPEAT_32(0),         // [0x80..0xA0) various special symbols ignored
    //--------------------------------------------------------------------------------
    REPEAT_8(0),  0xD0, 0, 0, 0, REPEAT_4(0), // [0xA0..0xB0) Ё = 0xF0 - 0x20
    REPEAT_8(0),  0xD1, 0, 0, 0, REPEAT_4(0), // [0xB0..0xC0) ё = 0xF1 - 0x20
    ROW_32_ASCENDING(0x60), // [0xC0..0xE0) = 0x80 - 0x20                 <  CYRILLIC
    ROW_16_ASCENDING(0x80), // [0xE0..0xF0) = 0xA0 - 0x20                 <  PART
    ROW_16_ASCENDING(0xC0)  // [0xF0..0xFF] = 0xE0 - 0x20
};
