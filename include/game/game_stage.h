#ifndef GAME_STAGE_H
#define GAME_STAGE_H

#include <memory>
#include <cstdint>
#include <vector>
#include <queue>
#include <tuple>

struct ResourceFile;
struct SOASpriteRGB;
struct SOASpritePal;
struct Sprite256;
struct Font16;
struct TileMap;

namespace Game {
    struct MouseState;
    namespace GameStage {
        struct GameStageShared {
            uint8_t* terrain_tile_high_byte_cache;
            uint8_t* terrain_tile_low_byte_cache;
            uint8_t* terrain_tile_u_cache;
            uint8_t* terrain_tile_v_cache;
            uint8_t* terrain_tile_i_cache;
            uint8_t* terrain_tile_j_cache;
            uint32_t camera_x;
            uint32_t camera_y;
        };

        enum class object_state {alive, burning, dead};

        enum class renderer_kind {object, unit, structure, structure_bottom, object_shadow, unit_shadow, structure_shadow, structure_bottom_shadow};

        using renderer_entry = std::tuple<size_t, size_t, renderer_kind>;

        struct compare_renderer_entry {
            bool operator()(const renderer_entry& lhs, const renderer_entry& rhs) {
                auto [l_priority, l_id, l_kind] = lhs;
                auto [r_priority, r_id, r_kind] = rhs;
                if(l_priority != r_priority) {
                    return l_priority > r_priority;
                }
                if (
                    (l_kind == renderer_kind::object ||
                     l_kind == renderer_kind::unit ||
                     l_kind == renderer_kind::structure ||
                     l_kind == renderer_kind::structure_bottom
                    )
                    &&
                    (r_kind == renderer_kind::object_shadow ||
                     r_kind == renderer_kind::unit_shadow ||
                     r_kind == renderer_kind::structure_shadow ||
                     r_kind == renderer_kind::structure_bottom_shadow
                     )) {
                    return true;
                }
                return false;
            }
        };

        struct MapObject {
            MapObject(
                int32_t p_coord_x,
                int32_t p_coord_y,
                int32_t p_depth,
                int32_t p_phase_ticks_remain,
                int32_t p_current_phase,
                int32_t p_meta_id,
                object_state p_state,
                std::shared_ptr<Sprite256> p_sprite
            );

            int32_t coord_x;
            int32_t coord_y;
            int32_t depth;
            int32_t phase_ticks_remain;
            int32_t current_phase;
            int32_t meta_id;
            object_state state;
            std::shared_ptr<Sprite256> sprite;
        };

        struct Structure {
            Structure(
                int32_t p_coord_x,
                int32_t p_coord_y,
                int32_t p_depth,
                int32_t p_phase_ticks_remain,
                int32_t p_current_phase,
                int32_t p_meta_id,
                uint16_t p_bridge_info_id,
                uint16_t p_fraction_id,
                uint16_t p_health,
                std::shared_ptr<Sprite256> p_sprite
            );

            int32_t coord_x;
            int32_t coord_y;
            int32_t depth;
            int32_t phase_ticks_remain;
            int32_t current_phase;
            int32_t meta_id;
            uint16_t bridge_info_id;
            uint16_t fraction_id;
            uint16_t health;
            std::shared_ptr<Sprite256> sprite;
        };

        struct Stage {
            Stage(uint16_t window_width,
                  uint16_t window_height);

            void load_level(uint8_t level_id);

            void on_enter();
            void update(const MouseState& mouse_state);
            void render(SOASpriteRGB &background_sprite);
            ~Stage();
        private:
            void update_scrolling();
            void update_scrolling(uint16_t left, uint16_t right, uint16_t top, uint16_t bottom);
            void recalc_lighting();

            void draw_tiles(SOASpriteRGB& back_sprite);
            void send_objects_to_render();
            void send_structures_to_render();
            void draw_wireframe(SOASpriteRGB& back_sprite);

            enum {
                NO_ID = 255,
                NO_BRIDGE = 65535,
                BRIGDE_STRIDE = 3,
                LEFT_BORDER = 0,
                HORIZONTAL_CENTER = 1,
                RIGHT_BORDER = 2,
                TOP_BORDER = 0,
                VERTICAL_CENTER = 1,
                BOTTOM_BORDER = 2
            };

            uint8_t water_offset_;
            uint16_t window_width_;
            uint16_t window_height_;

            uint32_t max_camera_x_;
            uint32_t max_camera_y_;

            uint8_t* terrain_cache_;
            GameStageShared render_shared_;

            std::vector<std::shared_ptr<SOASpritePal>> tiles_[4]{
                std::vector<std::shared_ptr<SOASpritePal>>{},
                std::vector<std::shared_ptr<SOASpritePal>>{},
                std::vector<std::shared_ptr<SOASpritePal>>{},
                std::vector<std::shared_ptr<SOASpritePal>>{}
            };
            std::unique_ptr<TileMap> tile_map_ptr_;
            std::vector<MapObject> map_objects_;
            std::vector<Structure> structures_;
            std::vector<std::tuple<uint8_t, uint8_t>> bridge_info_entries_;
            std::shared_ptr<Font16> debug_font_;

            std::priority_queue<renderer_entry, std::vector<renderer_entry>, compare_renderer_entry> render_queue_;
            int32_t shadow_offset_;
            //void handle_button_click(uint8_t button_id);

            //bool mouse_down_;


        };
    }
}

#endif /* end of include guard: GAME_STAGE_H */
