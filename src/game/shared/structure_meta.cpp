#include <game/shared/shared_res.h>
#include <game/shared/structure_meta.h>
#include <util/macro_shared.h>
#include <loaders/resource_file.h>
#include <loaders/registry_file.h>
#include <graphics/Sprite256.h>
#include <vector>
#include <string>

namespace Game {
namespace Meta {
    StructureMetaEntry::StructureMetaEntry(
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
    ) : id{p_id},
        file_name{p_file_name},
        tile_width{p_tile_width},
        tile_height{p_tile_height},
        full_height{p_full_height},
        selection_x1{p_selection_x1},
        selection_y1{p_selection_y1},
        selection_x2{p_selection_x2},
        selection_y2{p_selection_y2},
        shadow_y{p_shadow_y},
        phases_count{p_phases_count},
        anim_mask{p_anim_mask},
        anim_frames{p_anim_frames},
        anim_times{p_anim_times},
        picture{p_picture},
        light_radius{p_light_radius},
        light_pulse{p_light_pulse},
        usable{p_usable},
        indestructible{p_indestructible},
        flat{p_flat},
        variable_size{p_variable_size}
    {}

    StructureMeta::StructureMeta() {
        auto& graphic_resources = Game::Resources::Graphics();
        auto [success, structures_reg] = graphic_resources.read_registry_res_unique("structures/structures.reg");
        if(!success) {
            throw std::runtime_error("structures/structures.reg not found");
        }

        LOG("Reading Global/Count");

        auto [count_res, struct_count] = structures_reg->get_int("Global/Count");
        if(!count_res) {
            throw std::runtime_error("failed to read global info from structures.reg");
        }

        LOG("Reading structures meta");
        {
            char buffer[256];
            entries_.reserve(static_cast<size_t>(struct_count));
            sprites_.reserve(static_cast<size_t>(struct_count));
            for(int32_t i = 0; i < struct_count; ++i) {
                sprintf(buffer, "Structure%d/", i);
                auto [id, file_name, tile_width, tile_height, full_height] =
                    structures_reg->read_record(
                        buffer,
                        IntField{"ID"},
                        StringField{"File"},
                        IntField{"TileWidth"},
                        IntField{"TileHeight"},
                        IntField{"FullHeight"}
                    );

                auto [selection_x1, selection_y1, selection_x2, selection_y2] =
                        structures_reg->read_record(
                            buffer,
                            IntField{"SelectionX1"},
                            IntField{"SelectionY1"},
                            IntField{"SelectionX2"},
                            IntField{"SelectionY2"}
                        );

                auto [shadow_y, phases_count, anim_mask] =
                        structures_reg->read_record(
                            buffer,
                            IntField{"ShadowY"},
                            IntField{"Phases"},
                            StringField{"AnimMask"}
                        );

                auto [anim_frames, anim_times] =
                        structures_reg->read_record(
                            buffer,
                            IntArrayField{"AnimFrame"},
                            IntArrayField{"AnimTime"}
                        );

                auto [picture, light_radius, light_pulse] =
                        structures_reg->read_record(
                            buffer,
                            StringField{"Picture"},
                            IntField{"LightRadius"},
                            IntField{"LightPulse"}
                        );

                auto [usable, indestructible, variable_size, flat] =
                        structures_reg->read_record(
                            buffer,
                            IntField{"Usable"},
                            IntField{"Indestructible"},
                            IntField{"VariableSize"},
                            IntField{"Flat"}
                        );

                std::string file_entry;
                file_entry.reserve(file_name.content.size());
                for(size_t j = 0; j < file_name.content.size(); ++j) {
                    char cur_char = file_name.content[j];
                    if(cur_char == '\\') {
                        file_entry.push_back('/');
                    } else if(cur_char >= 'A' && cur_char <= 'Z') {
                        file_entry.push_back('a' + (cur_char - 'A'));
                    } else {
                        file_entry.push_back(cur_char);
                    }
                }
                sprintf(buffer, "structures/%s.256", file_entry.c_str());
                auto [sprite_res, sprite] = graphic_resources.read_256_shared(buffer);
                sprites_.push_back(sprite); // there are some files that are missing in a .res file,
                                            // this is how it was in original, so we forced to ignore sprite_res content

                entries_.emplace_back(
                    id.exists ? id.content : -1,
                    file_name.exists ? std::move(file_name.content) : "",
                    tile_width.exists ? tile_width.content : -1,
                    tile_height.exists ? tile_height.content : -1,
                    full_height.exists ? full_height.content : -1,
                    selection_x1.exists ? selection_x1.content : -1,
                    selection_y1.exists ? selection_y1.content : -1,
                    selection_x2.exists ? selection_x2.content : -1,
                    selection_y2.exists ? selection_y2.content : -1,
                    shadow_y.exists ? shadow_y.content : -1,
                    phases_count.exists ? phases_count.content : -1,
                    anim_mask.exists ? std::move(anim_mask.content) : "",
                    std::move(anim_frames.content), // when array not exists this field hold empty vector
                    std::move(anim_times.content), // when array not exists this field hold empty vector
                    picture.exists ? std::move(picture.content) : "",
                    light_radius.exists ? light_radius.content : -1,
                    light_pulse.exists ? light_pulse.content : -1,
                    usable.exists ? usable.content : -1,
                    indestructible.exists ? indestructible.content : -1,
                    variable_size.exists ? variable_size.content : -1,
                    flat.exists ? flat.content : -1
                );
            }
        }
    }

    const std::vector<StructureMetaEntry>& StructureMeta::info() const {
        return entries_;
    }

    const std::vector<std::shared_ptr<Sprite256>>& StructureMeta::sprites() const {
        return sprites_;
    }

    const StructureMeta& Structures() {
        static StructureMeta meta;
        return meta;
    }
}
}
