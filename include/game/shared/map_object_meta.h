#ifndef MAP_OBJECT_META_H
#define MAP_OBJECT_META_H

#include <cstdint>
#include <vector>
#include <string>
#include <memory>

struct Sprite256;

/* Reg file contains some importaint values
 *   related to object count and file count.
 *   File count is smaller than object count.
 *   Fields have self-explanatory names.
 *
 *   Fields are:
 *     Global/ObjectCount : Int
 *     Global/FileCount : int
 *
 * FileName fields for each file are stored in
 *   Files directory and has a name of a form "FileX"
 *   where X is a order number of a file. Each such field
 *   contains a path to the corresponding object graphics file
 *
 * Object info stored straight in a root in directories with
 *   a name of a form "ObjectX" where X is a order number of
 *   an object.
 *
 * Interesting fields in reg file for individual object are:
 *   ID : Int
 *     ID of an object.
 *     This is used for references between objects
 *     such as link to Parent, DeadObject or FireObject)
 *   File : Int
 *     ID of a file this file relates to
 *
 *   Index : Int
 *     Field of unknown nature.
 *     Theory -- it may be an identifier in data.bin or directly
 *     an identifier from alm in objects section)
 *     It seems that in practice this field has no use
 *
 *   Width : Int (Fixed point scale)
 *   Height : Int (Fixed point scale)
 *   CenterX : Int (Center X in fixed point coordinates)
 *   CenterY : Int (Center Y in fixed point coordinates)
 *
 *   Phases : Int
 *     In fact, this is a frame count, but as long as frames
 *     can be duplicated, its more nice to name it phases
 *   AnimationTime : IntArray
 *     Constains count of ticks each phase sould be shown on a screen
 *   AnimationFrame : IntArray
 *     contains frame_id for each phase
 *
 *   DeadObject : Int
 *     ID of an object for which we should "replace"
 *     an object when it becomes dead
 *   FireObject : Int
 *     ID of an object for which we should "replace"
 *     an object when it becomes on fire
 *     It seems that in practice this field has no use
 *
 *   Parent : Int (We have "incomplete" objects sometimes. This objects inherit missing properties from a parent)
 *
 *   InMapEditor : Int (Visibility in map editor (1 -- visible, 0 -- invisible))
 *   IconID : Int (Something map editor related probably)
 *   DescText : String (Textual description of an object)
 */

namespace Game {
namespace Meta {

struct MapObjectMetaEntry {
    MapObjectMetaEntry(
        int32_t p_id,
        int32_t p_file_id,
        int32_t p_parent_id,
        int32_t p_dead_id,
        int32_t p_fixed_w,
        int32_t p_fixed_h,
        int32_t p_center_x,
        int32_t p_center_y,
        int32_t p_phases_count,
        std::vector<int32_t> p_anim_times,
        std::vector<int32_t> p_anim_frames
    );

    int32_t id;
    int32_t file_id;
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
