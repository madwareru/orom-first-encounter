#include <game/shared/shared_res.h>
#include <game/shared/map_object_meta.h>
#include <util/macro_shared.h>
#include <loaders/resource_file.h>
#include <loaders/registry_file.h>
#include <graphics/Sprite256.h>
#include <vector>
#include <string>

namespace {
    enum class mark {white, gray, black};
}

namespace Game {
namespace Meta {
    MapObjectMetaEntry::MapObjectMetaEntry(
        int32_t p_id,
        int32_t p_file_id,
        int32_t p_parent_id,
        int32_t p_dead_id,
        int32_t p_fixed_w,
        int32_t p_fixed_h,
        int32_t p_center_x,
        int32_t p_center_y,
        int32_t p_phases_count,
        std::vector<int32_t>&& p_anim_times,
        std::vector<int32_t>&& p_anim_frames
    ) : id{p_id},
        file_id{p_file_id},
        parent_id{p_parent_id},
        dead_id{p_dead_id},
        fixed_w{p_fixed_w},
        fixed_h{p_fixed_h},
        center_x{p_center_x},
        center_y{p_center_y},
        phases_count{p_phases_count},
        anim_times{p_anim_times},
        anim_frames{p_anim_frames}
    {}

    static inline void ensure(std::vector<MapObjectMetaEntry>& info_vec, std::vector<mark>& marker_vec, size_t id) {
#define ENSURE_INT(x) if(info_vec[id].x == -1 && parent_entry.x != -1) info_vec[id].x = parent_entry.x
#define ENSURE_INT_ARRAY(x) if(info_vec[id].x.size() == 0 && parent_entry.x.size() != 0) info_vec[id].x = parent_entry.x
        if(marker_vec[id] == mark::black) {
            return;
        }
        if(marker_vec[id] == mark::gray) {
            throw std::runtime_error("found a cyclic dependency. Nothing could be done");
        }
        marker_vec[id] = mark::gray;
        if(info_vec[static_cast<size_t>(info_vec[id].parent_id)].parent_id != -1) {
            ensure(info_vec, marker_vec, static_cast<size_t>(info_vec[id].parent_id));
        }
        const auto& parent_entry = info_vec[static_cast<size_t>(info_vec[id].parent_id)];

        ENSURE_INT(dead_id);
        ENSURE_INT(file_id);
        ENSURE_INT(fixed_w);
        ENSURE_INT(fixed_h);
        ENSURE_INT(center_x);
        ENSURE_INT(center_y);
        ENSURE_INT(phases_count);

        ENSURE_INT_ARRAY(anim_times);
        ENSURE_INT_ARRAY(anim_frames);

        marker_vec[id] = mark::black;
#undef ENSURE_INT
#undef ENSURE_INT_ARRAY
    }

    static inline void ensure(std::vector<MapObjectMetaEntry>& info_vec, std::vector<mark>& marker_vec) {
        for(size_t i = 0; i < info_vec.size(); ++i) {
            if(marker_vec[i] == mark::black) continue;
            if(info_vec[i].parent_id == -1) continue;
            ensure(info_vec, marker_vec, i);
        }
    }

    MapObjectMeta::MapObjectMeta() {
        auto& graphic_resources = Game::Resources::Graphics();
        auto [success, objects_reg] = graphic_resources.read_registry_res_unique("objects/objects.reg");
        if(!success) {
            throw std::runtime_error("objects/objects.reg not found");
        }

        LOG("Reading Globals");

        auto [obj_count_res, obj_count] = objects_reg->get_int("Global/ObjectCount");
        auto [file_count_res, file_count] = objects_reg->get_int("Global/FileCount");

        if(!(obj_count_res && file_count_res)) {
            throw std::runtime_error("failed to read global info from objects.reg");
        }

        LOG("Reading map object file names");
        {
            sprites_.reserve(static_cast<size_t>(file_count));
            for(int32_t i = 0; i < file_count; ++i) {
                char buffer[64];
                sprintf(buffer, "Files/File%d", i);
                auto[f_res, file_name] = objects_reg->get_string(buffer);
                if(!f_res) {
                    throw std::runtime_error("failed to read file_name information for map object");
                }
                std::string file_entry;
                file_entry.reserve(file_name.size());
                for(size_t j = 0; j < file_name.size(); ++j) {
                    char cur_char = file_name[j];
                    if(cur_char == '\\') {
                        file_entry.push_back('/');
                    } else {
                        file_entry.push_back(cur_char);
                    }
                }
                sprintf(buffer, "objects/%s.256", file_entry.c_str());

                auto [sprite_res, sprite] = graphic_resources.read_256_shared(buffer);
                sprites_.push_back(sprite); // there are some files that are missing in a .res file,
                                            // this is how it was in original, so we forced to ignore sprite_res content
            }
        }

        LOG("Reading map object meta");
        {
            entries_.reserve(static_cast<size_t>(obj_count));
            for(int32_t i = 0; i < obj_count; ++i) {
                char buffer[16];
                sprintf(buffer, "Object%d/", i);
                auto [id, file_id, parent_id, dead_id] =
                    objects_reg->read_record(
                        buffer,
                        IntField{"ID"},
                        IntField{"File"},
                        IntField{"Parent"},
                        IntField{"DeadObject"}
                    );

                auto [fixed_w, fixed_h, center_x, center_y] =
                    objects_reg->read_record(
                        buffer,
                        IntField{"Width"},
                        IntField{"Height"},
                        IntField{"CenterX"},
                        IntField{"CenterY"}
                    );

                auto [phases_count, anim_times, anim_frames] =
                    objects_reg->read_record(
                        buffer,
                        IntField{"Phases"},
                        IntArrayField{"AnimationTime"},
                        IntArrayField{"AnimationFrame"}
                    );

                entries_.emplace_back(
                    id.exists ? id.content : -1,
                    file_id.exists ? file_id.content : -1,
                    parent_id.exists ? parent_id.content : -1,
                    dead_id.exists ? dead_id.content : -1,
                    fixed_w.exists ? fixed_w.content : -1,
                    fixed_h.exists ? fixed_h.content : -1,
                    center_x.exists ? center_x.content : -1,
                    center_y.exists ? center_y.content : -1,
                    phases_count.exists ? phases_count.content : -1,
                    std::move(anim_times.content), // when array not exists this field hold empty vector
                    std::move(anim_frames.content) // when array not exists this field hold empty vector
                );
            }

            std::vector<mark> marker_vec;
            marker_vec.reserve(static_cast<size_t>(obj_count));
            for(int32_t i = 0; i < obj_count; ++i) {
                marker_vec.push_back(mark::white);
            }
            ensure(entries_, marker_vec);
        }
    }

    const std::vector<MapObjectMetaEntry>& MapObjectMeta::info() const {
        return entries_;
    }

    const std::vector<std::shared_ptr<Sprite256>>& MapObjectMeta::sprites() const {
        return sprites_;
    }

    const MapObjectMeta& MapObjects() {
        static MapObjectMeta meta;
        return meta;
    }
}
}
