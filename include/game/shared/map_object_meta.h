#ifndef MAP_OBJECT_META_H
#define MAP_OBJECT_META_H

#include <cstdint>
#include <vector>
#include <string>
#include <memory>

struct Sprite256;

namespace Game {
namespace Meta {

struct MapObjectMetaEntry {
    MapObjectMetaEntry(
        int32_t p_id,
        int32_t p_file_id,
        int32_t p_index,
        int32_t p_parent_id,
        int32_t p_dead_id,
        int32_t p_fixed_w,
        int32_t p_fixed_h,
        int32_t p_center_x,
        int32_t p_center_y,
        int32_t p_phases_count,
        std::vector<int32_t>&& p_anim_times,
        std::vector<int32_t>&& p_anim_frames
    );

    int32_t id;
    int32_t file_id;
    int32_t index;
    int32_t parent_id;
    int32_t dead_id;

    int32_t fixed_w;
    int32_t fixed_h;
    int32_t center_x;
    int32_t center_y;

    int32_t phases_count;
    std::vector<int32_t> anim_times;
    std::vector<int32_t> anim_frames;
};

struct MapObjectMeta {
    MapObjectMeta();
    const std::vector<MapObjectMetaEntry>& info() const ;
    const std::vector<std::shared_ptr<Sprite256>>& sprites() const;
private:
    std::vector<MapObjectMetaEntry> entries_;
    std::vector<std::shared_ptr<Sprite256>> sprites_;
};

const MapObjectMeta& MapObjects();

}
}

#endif // MAP_OBJECT_META_H
