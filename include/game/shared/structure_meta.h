#ifndef STRUCTURE_META_H
#define STRUCTURE_META_H


#include <cstdint>
#include <vector>
#include <string>
#include <memory>

struct Sprite256;

namespace Game {
namespace Meta {

struct StructureMetaEntry {
    StructureMetaEntry(
        int32_t p_id,
        std::string&& p_file_name,
        int32_t p_tile_width,
        int32_t p_tile_height,
        int32_t p_full_height,
        int32_t p_selection_x1,
        int32_t p_selection_y1,
        int32_t p_selection_x2,
        int32_t p_selection_y2,
        int32_t p_shadow_y,
        int32_t p_phases_count,
        std::string&& p_anim_mask,
        std::vector<int32_t>&& p_anim_frames,
        std::vector<int32_t>&& p_anim_times,
        std::string&& p_picture,
        int32_t p_light_radius,
        int32_t p_light_pulse,
        int32_t p_usable,
        int32_t p_indestructible,
        int32_t p_flat,
        int32_t p_variable_size
    );

    int32_t id;
    std::string file_name;
    int32_t tile_width;
    int32_t tile_height;
    int32_t full_height;
    int32_t selection_x1;
    int32_t selection_y1;
    int32_t selection_x2;
    int32_t selection_y2;
    int32_t shadow_y;
    int32_t phases_count;
    std::string anim_mask;
    uint8_t anim_mask_stride;
    std::vector<int32_t> anim_mask_shifts;
    std::vector<int32_t> anim_frames;
    std::vector<int32_t> anim_times;
    std::string picture;
    int32_t light_radius;
    int32_t light_pulse;
    int32_t usable;
    int32_t indestructible;
    int32_t flat;
    int32_t variable_size;
};

struct StructureMeta {
    StructureMeta();
    const std::vector<StructureMetaEntry>& info() const ;
    const std::vector<std::shared_ptr<Sprite256>>& sprites() const;
private:
    std::vector<StructureMetaEntry> entries_;
    std::vector<std::shared_ptr<Sprite256>> sprites_;
};

const StructureMeta& Structures();

}
}


#endif // STRUCTURE_META_H
