#include <game/game_stage.h>

#include <loaders/resource_file.h>
#include <graphics/soaspritergb.h>
#include <graphics/tilemap/tilemap.h>
#include <loaders/ksy/rage_of_mages_1_alm.h>
#include <util/macro_shared.h>

namespace Game {
    namespace GameStage {
        Stage::Stage(std::shared_ptr<ResourceFile> graphic_resources,
                     std::shared_ptr<ResourceFile> scenario_resources,
                     uint16_t window_width,
                     uint16_t window_height) :
                window_width_{window_width},
                window_height_{window_height},
                scenario_resources_{scenario_resources} {
            terrain_cache_ = new uint8_t[4 * window_width_ * window_height_];
            size_t offset = 0;

            render_shared_.terrain_tile_x_cache = &terrain_cache_[offset];
            offset += window_width * window_height;
            render_shared_.terrain_tile_y_cache = &terrain_cache_[offset];
            offset += window_width * window_height;
            render_shared_.terrain_tile_u_cache = &terrain_cache_[offset];
            offset += window_width * window_height;
            render_shared_.terrain_tile_v_cache = &terrain_cache_[offset];
            render_shared_.camera_x = 0;
            render_shared_.camera_y = 0;

            graphic_resources_ = graphic_resources;

            tile_map_ptr_ = std::unique_ptr<TileMap>{nullptr};

            char buf[32];
            for(size_t i = 1; i <= 4; ++i) {
                const size_t capacity = (i < 4) ? 16 : 4;
                tiles_[i-1].reserve(capacity);
                for(size_t j = 0; j < capacity; ++j)
                {
                    if(j < 10) {
                        sprintf(buf, "terrain/tile%d-0%d.bmp", (int)i, (int)j);
                    } else {
                        sprintf(buf, "terrain/tile%d-%d.bmp", (int)i, (int)j);
                    }
                    auto[success, next_bmp] = graphic_resources_->read_bmp_shared(buf);
                    if(success) {
                        tiles_[i-1].emplace_back(next_bmp);
                    }
                }
            }
        }

        void Stage::load_level(uint8_t level_id) {
            char buffer[16];
            sprintf(buffer, "%u.alm", level_id);
            auto resource_header = scenario_resources_->get_resource(buffer);
            if(resource_header == nullptr) {
                LOG_ERROR("could not load resource " << buffer);
                return;
            }

            std::string bytes = resource_header->bytes();
            kaitai::kstream ks(bytes);
            rage_of_mages_1_alm_t alm{&ks};

            auto alm_header = alm.alm_header();
            auto general_map_info = alm.general_map_info();

            LOG("SECTION COUNT: " << alm_header->section_count());
            LOG("W: " << general_map_info->width());
            LOG("H: " << general_map_info->height());


            tile_map_ptr_.release();
            tile_map_ptr_ = std::make_unique<TileMap>(
                general_map_info->width(),
                general_map_info->height()
            );

            //read_tiles

            uint8_t tiles_id = 255;
            uint8_t height_map_id = 255;

            for(uint8_t i = 0; i < alm.sections()->size(); ++i) {
                const rage_of_mages_1_alm_t::alm_section_t* section_info = alm.sections()->at(i);

                switch (section_info->header()->section_kind()) {
                    case rage_of_mages_1_alm_t::SECTION_KIND_E_TILES:
                        tiles_id = i;
                        break;
                    case rage_of_mages_1_alm_t::SECTION_KIND_E_HEIGHT_MAP:
                        height_map_id = i;
                        break;
                    default: break;
                }
            }

            if(tiles_id == 255 || height_map_id == 255) {
                LOG_ERROR("there was an error while retrieving tilemap data");
                return;
            }

            const auto tiles_data =
                dynamic_cast<rage_of_mages_1_alm_t::tiles_sec_t*>(
                    alm.sections()->at(tiles_id)->body()
                );
            const auto height_map_data =
                dynamic_cast<rage_of_mages_1_alm_t::height_map_sec_t*>(
                    alm.sections()->at(height_map_id)->body()
                );

            if(tiles_data == nullptr || height_map_data == nullptr) {
                LOG_ERROR("there was an error while retrieving tilemap data (dynamic cast)");
                return;
            }

            const auto tiles = *(tiles_data->tiles());
            const auto height_map = *(height_map_data->heights());

            if(tiles.size() % 8 != 0) {
                LOG_ERROR("hmm...");
            }

            size_t t_stride = general_map_info->width();
            size_t h_stride = general_map_info->width()+1;

            size_t t_offset = 0;
            size_t h_offset = 0;

            for(uint8_t y = 0; y < general_map_info->height(); ++y) {
                int16_t min_y = static_cast<int16_t>(y * 32);
                int16_t max_y = static_cast<int16_t>(min_y + 32);
                for(uint8_t i = 0; i < general_map_info->width(); i += 8) {
                    TileMapChunk chunk;
                    chunk.start_tile_i = i;
                    chunk.tile_j = y;
                    int16_t local_min_y = min_y;
                    int16_t local_max_y = max_y - 255;
                    for(size_t j = 0; j < 8; ++j) {
                        const auto tile = tiles[t_offset + i + j];
                        const auto height_tl = height_map[h_offset + i + j];
                        const auto height_tr = height_map[h_offset + i + j + 1];
                        const auto height_bl = height_map[h_offset + i + j + h_stride];
                        const auto height_br = height_map[h_offset + i + j + h_stride + 1];

                        chunk.tile_id[j] = tile->tile_id();
                        chunk.top_heights[j * 2] = height_tl;
                        if(min_y - height_tl < local_min_y) {
                            local_min_y = min_y - height_tl;
                        }
                        chunk.top_heights[j * 2 + 1] = height_tr;
                        if(min_y - height_tr < local_min_y) {
                            local_min_y = min_y - height_tr;
                        }
                        chunk.bottom_heights[j * 2] = height_bl;
                        if(max_y - height_bl > local_max_y) {
                            local_max_y = max_y - height_bl;
                        }
                        chunk.bottom_heights[j * 2 + 1] = height_br;
                        if(max_y - height_br > local_max_y) {
                            local_max_y = max_y - height_br;
                        }
                    }
                    chunk.min_y = local_min_y;
                    chunk.max_y = local_max_y;
                    tile_map_ptr_->add_chunk(chunk);
                }
                t_offset += t_stride;
                h_offset += h_stride;
            }
            LOG("FINISHED LOADING TILEMAP DATA");
        }

        Stage::~Stage() {
            delete [] terrain_cache_;
        }

        void Stage::update(const MouseState &mouse_state) {

        }

        void Stage::render(SOASpriteRGB &background_sprite) {
            size_t x = 0;
            size_t y = 0;
            for(auto tileset : tiles_) {
                for(auto tile : tileset) {
                    tile->blit_on_sprite(background_sprite, x, y);
                    x += 32;
                    if(x >= 1024) {
                        x %= 1024;
                        y += 32 * 14;
                    }
                }
            }
        }

        void Stage::on_enter() {

        }
    }
}