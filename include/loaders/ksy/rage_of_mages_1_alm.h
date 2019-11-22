#ifndef RAGE_OF_MAGES_1_ALM_H_
#define RAGE_OF_MAGES_1_ALM_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include <kaitaistruct.h>

#include <stdint.h>
#include <vector>

class rage_of_mages_1_alm_t : public kaitai::kstruct {

public:
    class alm_section_t;
    class trigger_entry_t;
    class map_objects_sec_t;
    class instance_entry_t;
    class structures_sec_t;
    class sacks_sec_t;
    class general_map_info_sec_t;
    class fractions_sec_t;
    class effect_modifier_t;
    class height_map_sec_t;
    class bridge_info_t;
    class section_header_t;
    class check_entry_t;
    class alm_header_t;
    class triggers_sec_t;
    class structure_entry_t;
    class unit_entry_t;
    class fraction_entry_t;
    class tiles_sec_t;
    class item_entry_t;
    class sack_entry_t;
    class effects_sec_t;
    class effect_entry_t;
    class units_sec_t;
    class tile_entry_t;

    enum check_type_t {
        CHECK_TYPE_UNKNOWN = 0,
        CHECK_TYPE_GROUP_UNIT_COUNT = 1,
        CHECK_TYPE_IS_UNIT_IN_A_BOX = 2,
        CHECK_TYPE_IS_UNIT_IN_A_CIRCLE = 3,
        CHECK_TYPE_GET_UNIT_PARAMETER = 4,
        CHECK_TYPE_IS_UNIT_ALIVE = 5,
        CHECK_TYPE_GET_DISTANCE_BETWEEN_UNITS = 6,
        CHECK_TYPE_GET_DISTANCE_FROM_POINT_TO_UNIT = 7,
        CHECK_TYPE_HOW_MANY_UNITS_FRACTION_HAVE = 8,
        CHECK_TYPE_IS_UNIT_ATTACKED = 9,
        CHECK_TYPE_GET_DIPLOMACY = 10,
        CHECK_TYPE_CHECK_SACK = 11,
        CHECK_TYPE_GET_DISTANCE_TO_NEAREST_FRACTION_UNIT = 15,
        CHECK_TYPE_GET_DISTANCE_FROM_POINT_TO_UNIT_WITH_ITEM = 16,
        CHECK_TYPE_IS_ITEM_IN_SACK = 17,
        CHECK_TYPE_VIP = 18,
        CHECK_TYPE_CHECK_VARIABLE = 19,
        CHECK_TYPE_HOW_MANY_STRUCTURES_FRACTION_HAVE = 20,
        CHECK_TYPE_GET_STRUCTURE_HEALTH = 21,
        CHECK_TYPE_TELEPORT = 22,
        CHECK_TYPE_CHECK_SCENARIO_VARIABLE = 23,
        CHECK_TYPE_CHECK_SUB_OBJECTIVE = 24,
        CHECK_TYPE_SPELL_IN_AREA = 25,
        CHECK_TYPE_SPELL_ON_UNIT = 26,
        CHECK_TYPE_IS_UNIT_IN_POINT = 27,
        CHECK_TYPE_CONSTANT = 65538
    };

    enum section_kind_e_t {
        SECTION_KIND_E_GENERAL = 0,
        SECTION_KIND_E_TILES = 1,
        SECTION_KIND_E_HEIGHT_MAP = 2,
        SECTION_KIND_E_MAP_OBJECTS = 3,
        SECTION_KIND_E_STRUCTURES = 4,
        SECTION_KIND_E_FRACTIONS = 5,
        SECTION_KIND_E_UNITS = 6,
        SECTION_KIND_E_TRIGGERS = 7,
        SECTION_KIND_E_SACKS = 8,
        SECTION_KIND_E_EFFECTS = 9
    };

    enum check_operator_t {
        CHECK_OPERATOR_EQUALS = 0,
        CHECK_OPERATOR_NOT_EQUALS = 1,
        CHECK_OPERATOR_GREATER_THAN = 2,
        CHECK_OPERATOR_LOWER_THAN = 3,
        CHECK_OPERATOR_GREATER_THAN_EQUALS = 4,
        CHECK_OPERATOR_LOWER_THAN_EQUALS = 5
    };

    enum argument_type_t {
        ARGUMENT_TYPE_NUMBER = 1,
        ARGUMENT_TYPE_GROUP = 2,
        ARGUMENT_TYPE_FRACTION = 3,
        ARGUMENT_TYPE_UNIT = 4,
        ARGUMENT_TYPE_X = 5,
        ARGUMENT_TYPE_Y = 6,
        ARGUMENT_TYPE_CONSTANT = 7,
        ARGUMENT_TYPE_ITEM = 8,
        ARGUMENT_TYPE_STRUCTURE = 9
    };

    enum instance_type_t {
        INSTANCE_TYPE_UNKNOWN = 0,
        INSTANCE_TYPE_INCREMENT_MISSION_STAGE = 1,
        INSTANCE_TYPE_SEND_MESSAGE = 2,
        INSTANCE_TYPE_SET_VARIABLE_VALUE = 3,
        INSTANCE_TYPE_FORCE_MISSION_COMPLETE = 4,
        INSTANCE_TYPE_FORCE_MISSION_FAILED = 5,
        INSTANCE_TYPE_COMMAND = 6,
        INSTANCE_TYPE_KEEP_FORMATION = 7,
        INSTANCE_TYPE_INCREMENT_VARIABLE = 8,
        INSTANCE_TYPE_SET_DIPLOMACY = 10,
        INSTANCE_TYPE_GIVE_ITEM = 11,
        INSTANCE_TYPE_ADD_ITEM_IN_UNITS_SACK = 12,
        INSTANCE_TYPE_REMOVE_ITEM_FROM_UNITS_SACK = 13,
        INSTANCE_TYPE_HIDE_UNIT = 16,
        INSTANCE_TYPE_SHOW_UNIT = 17,
        INSTANCE_TYPE_METAMORPH_UNIT = 18,
        INSTANCE_TYPE_CHANGE_UNITS_OWNER = 19,
        INSTANCE_TYPE_DROP_ALL = 20,
        INSTANCE_TYPE_MAGIC_ON_AREA = 21,
        INSTANCE_TYPE_CHANGE_GROUPS_OWNER = 22,
        INSTANCE_TYPE_GIVE_MONEY_TO_FRACTION = 23,
        INSTANCE_TYPE_MAGIC_ON_UNIT = 24,
        INSTANCE_TYPE_CREATE_MAGIC_TRIGGER = 25,
        INSTANCE_TYPE_SET_STRUCTURE_HEALTH = 26,
        INSTANCE_TYPE_MOVE_UNIT_IMMEDIATE = 27,
        INSTANCE_TYPE_GIVE_ALL_ITEMS_FROM_UNIT_TO_UNIT = 28,
        INSTANCE_TYPE_TIMED_SPELL_ON_GROUND = 30,
        INSTANCE_TYPE_CHANGE_RESPAWN_TIME = 31,
        INSTANCE_TYPE_HIDE_GROUP = 32,
        INSTANCE_TYPE_SHOW_GROUP = 33,
        INSTANCE_TYPE_SET_UNITS_PARAMETER = 34,
        INSTANCE_TYPE_SET_SCENARIO_VARIABLE = 35,
        INSTANCE_TYPE_SET_SUB_OBJECTIVE = 36,
        INSTANCE_TYPE_SET_MUSIC_ORDER = 37,
        INSTANCE_TYPE_REMOVE_ITEM_FROM_ALL = 38,
        INSTANCE_TYPE_STOP_GROUP = 39,
        INSTANCE_TYPE_START_HERE = 65538,
        INSTANCE_TYPE_RESPAWN_GROUP = 65539,
        INSTANCE_TYPE_CHANGE_MUSIC_TO = 65540
    };

    rage_of_mages_1_alm_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

private:
    void _read();

public:
    ~rage_of_mages_1_alm_t();

    class alm_section_t : public kaitai::kstruct {

    public:

        alm_section_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~alm_section_t();

    private:
        section_header_t* m_header;
        kaitai::kstruct* m_body;
        bool n_body;

    public:
        bool _is_null_body() { body(); return n_body; };

    private:
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t* m__parent;
        std::string m__raw_header;
        kaitai::kstream* m__io__raw_header;
        std::string m__raw_body;
        kaitai::kstream* m__io__raw_body;

    public:
        section_header_t* header() const { return m_header; }
        kaitai::kstruct* body() const { return m_body; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t* _parent() const { return m__parent; }
        std::string _raw_header() const { return m__raw_header; }
        kaitai::kstream* _io__raw_header() const { return m__io__raw_header; }
        std::string _raw_body() const { return m__raw_body; }
        kaitai::kstream* _io__raw_body() const { return m__io__raw_body; }
    };

    class trigger_entry_t : public kaitai::kstruct {

    public:

        trigger_entry_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::triggers_sec_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~trigger_entry_t();

    private:
        std::string m_name;
        std::vector<uint32_t>* m_check_identifiers;
        std::vector<uint32_t>* m_instance_identifiers;
        check_operator_t m_check_01_operator;
        check_operator_t m_check_23_operator;
        check_operator_t m_check_45_operator;
        uint32_t m_run_once_flag;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::triggers_sec_t* m__parent;

    public:
        std::string name() const { return m_name; }
        std::vector<uint32_t>* check_identifiers() const { return m_check_identifiers; }
        std::vector<uint32_t>* instance_identifiers() const { return m_instance_identifiers; }
        check_operator_t check_01_operator() const { return m_check_01_operator; }
        check_operator_t check_23_operator() const { return m_check_23_operator; }
        check_operator_t check_45_operator() const { return m_check_45_operator; }
        uint32_t run_once_flag() const { return m_run_once_flag; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::triggers_sec_t* _parent() const { return m__parent; }
    };

    class map_objects_sec_t : public kaitai::kstruct {

    public:

        map_objects_sec_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::alm_section_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~map_objects_sec_t();

    private:
        std::vector<uint8_t>* m_objects;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::alm_section_t* m__parent;

    public:
        std::vector<uint8_t>* objects() const { return m_objects; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::alm_section_t* _parent() const { return m__parent; }
    };

    class instance_entry_t : public kaitai::kstruct {

    public:

        instance_entry_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::triggers_sec_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~instance_entry_t();

    private:
        std::string m_name;
        instance_type_t m_type;
        uint32_t m_id;
        uint32_t m_execute_once_flag;
        std::vector<uint32_t>* m_argument_values;
        std::vector<argument_type_t>* m_argument_types;
        std::vector<std::string>* m_argument_names;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::triggers_sec_t* m__parent;

    public:
        std::string name() const { return m_name; }
        instance_type_t type() const { return m_type; }
        uint32_t id() const { return m_id; }
        uint32_t execute_once_flag() const { return m_execute_once_flag; }
        std::vector<uint32_t>* argument_values() const { return m_argument_values; }
        std::vector<argument_type_t>* argument_types() const { return m_argument_types; }
        std::vector<std::string>* argument_names() const { return m_argument_names; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::triggers_sec_t* _parent() const { return m__parent; }
    };

    class structures_sec_t : public kaitai::kstruct {

    public:

        structures_sec_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::alm_section_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~structures_sec_t();

    private:
        std::vector<structure_entry_t*>* m_structures;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::alm_section_t* m__parent;

    public:
        std::vector<structure_entry_t*>* structures() const { return m_structures; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::alm_section_t* _parent() const { return m__parent; }
    };

    class sacks_sec_t : public kaitai::kstruct {

    public:

        sacks_sec_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::alm_section_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~sacks_sec_t();

    private:
        std::vector<sack_entry_t*>* m_sacks;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::alm_section_t* m__parent;

    public:
        std::vector<sack_entry_t*>* sacks() const { return m_sacks; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::alm_section_t* _parent() const { return m__parent; }
    };

    class general_map_info_sec_t : public kaitai::kstruct {

    public:

        general_map_info_sec_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~general_map_info_sec_t();

    private:
        uint32_t m_width;
        uint32_t m_height;
        float m_negative_sun_angle;
        uint32_t m_time_in_minutes;
        uint32_t m_darkness;
        uint32_t m_contrast;
        uint32_t m_use_tiles;
        uint32_t m_fraction_count;
        uint32_t m_structure_count;
        uint32_t m_unit_count;
        uint32_t m_logic_count;
        uint32_t m_sack_count;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t* m__parent;

    public:
        uint32_t width() const { return m_width; }
        uint32_t height() const { return m_height; }
        float negative_sun_angle() const { return m_negative_sun_angle; }
        uint32_t time_in_minutes() const { return m_time_in_minutes; }
        uint32_t darkness() const { return m_darkness; }
        uint32_t contrast() const { return m_contrast; }
        uint32_t use_tiles() const { return m_use_tiles; }
        uint32_t fraction_count() const { return m_fraction_count; }
        uint32_t structure_count() const { return m_structure_count; }
        uint32_t unit_count() const { return m_unit_count; }
        uint32_t logic_count() const { return m_logic_count; }
        uint32_t sack_count() const { return m_sack_count; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t* _parent() const { return m__parent; }
    };

    class fractions_sec_t : public kaitai::kstruct {

    public:

        fractions_sec_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::alm_section_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~fractions_sec_t();

    private:
        std::vector<fraction_entry_t*>* m_fractions;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::alm_section_t* m__parent;

    public:
        std::vector<fraction_entry_t*>* fractions() const { return m_fractions; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::alm_section_t* _parent() const { return m__parent; }
    };

    class effect_modifier_t : public kaitai::kstruct {

    public:

        effect_modifier_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::effect_entry_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~effect_modifier_t();

    private:
        uint16_t m_modifier_type;
        uint32_t m_modifier_value;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::effect_entry_t* m__parent;

    public:
        uint16_t modifier_type() const { return m_modifier_type; }
        uint32_t modifier_value() const { return m_modifier_value; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::effect_entry_t* _parent() const { return m__parent; }
    };

    class height_map_sec_t : public kaitai::kstruct {

    public:

        height_map_sec_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::alm_section_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~height_map_sec_t();

    private:
        std::vector<uint8_t>* m_heights;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::alm_section_t* m__parent;

    public:
        std::vector<uint8_t>* heights() const { return m_heights; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::alm_section_t* _parent() const { return m__parent; }
    };

    class bridge_info_t : public kaitai::kstruct {

    public:

        bridge_info_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::structure_entry_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~bridge_info_t();

    private:
        uint32_t m_width;
        uint32_t m_height;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::structure_entry_t* m__parent;

    public:
        uint32_t width() const { return m_width; }
        uint32_t height() const { return m_height; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::structure_entry_t* _parent() const { return m__parent; }
    };

    class section_header_t : public kaitai::kstruct {

    public:

        section_header_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~section_header_t();

    private:
        uint32_t m_some_number;
        uint32_t m_header_size;
        uint32_t m_data_size;
        section_kind_e_t m_section_kind;
        uint32_t m_random_seed;
        rage_of_mages_1_alm_t* m__root;
        kaitai::kstruct* m__parent;

    public:

        /**
         * Number 7 or 5 with unknown purpose
         */
        uint32_t some_number() const { return m_some_number; }
        uint32_t header_size() const { return m_header_size; }
        uint32_t data_size() const { return m_data_size; }
        section_kind_e_t section_kind() const { return m_section_kind; }

        /**
         * this number is the same for all headers
         */
        uint32_t random_seed() const { return m_random_seed; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class check_entry_t : public kaitai::kstruct {

    public:

        check_entry_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::triggers_sec_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~check_entry_t();

    private:
        std::string m_name;
        check_type_t m_type;
        uint32_t m_id;
        uint32_t m_execute_once_flag;
        std::vector<uint32_t>* m_argument_values;
        std::vector<argument_type_t>* m_argument_types;
        std::vector<std::string>* m_argument_names;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::triggers_sec_t* m__parent;

    public:
        std::string name() const { return m_name; }
        check_type_t type() const { return m_type; }
        uint32_t id() const { return m_id; }
        uint32_t execute_once_flag() const { return m_execute_once_flag; }
        std::vector<uint32_t>* argument_values() const { return m_argument_values; }
        std::vector<argument_type_t>* argument_types() const { return m_argument_types; }
        std::vector<std::string>* argument_names() const { return m_argument_names; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::triggers_sec_t* _parent() const { return m__parent; }
    };

    class alm_header_t : public kaitai::kstruct {

    public:

        alm_header_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~alm_header_t();

    private:
        std::string m_magic;
        uint32_t m_header_size;
        uint32_t m_mysterious_size;
        uint32_t m_section_count;
        uint32_t m_random_seed;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t* m__parent;

    public:
        std::string magic() const { return m_magic; }
        uint32_t header_size() const { return m_header_size; }

        /**
         * 0x48 + H * W * 0x04
         */
        uint32_t mysterious_size() const { return m_mysterious_size; }
        uint32_t section_count() const { return m_section_count; }

        /**
         * this number is the same for all headers
         */
        uint32_t random_seed() const { return m_random_seed; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t* _parent() const { return m__parent; }
    };

    class triggers_sec_t : public kaitai::kstruct {

    public:

        triggers_sec_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::alm_section_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~triggers_sec_t();

    private:
        uint32_t m_instance_count;
        std::vector<instance_entry_t*>* m_instances;
        uint32_t m_check_count;
        std::vector<check_entry_t*>* m_checks;
        uint32_t m_trigger_count;
        std::vector<trigger_entry_t*>* m_triggers;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::alm_section_t* m__parent;

    public:
        uint32_t instance_count() const { return m_instance_count; }
        std::vector<instance_entry_t*>* instances() const { return m_instances; }
        uint32_t check_count() const { return m_check_count; }
        std::vector<check_entry_t*>* checks() const { return m_checks; }
        uint32_t trigger_count() const { return m_trigger_count; }
        std::vector<trigger_entry_t*>* triggers() const { return m_triggers; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::alm_section_t* _parent() const { return m__parent; }
    };

    class structure_entry_t : public kaitai::kstruct {

    public:

        structure_entry_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::structures_sec_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~structure_entry_t();

    private:
        uint32_t m_x_coord;
        uint32_t m_y_coord;
        uint32_t m_type_id;
        uint16_t m_health;
        uint32_t m_fraction_id;
        uint16_t m_id;
        bridge_info_t* m_bridge_details;
        bool n_bridge_details;

    public:
        bool _is_null_bridge_details() { bridge_details(); return n_bridge_details; };

    private:
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::structures_sec_t* m__parent;

    public:

        /**
         * (X Coord * 0x100) + 0x80 (sort of a fixed point value)
         */
        uint32_t x_coord() const { return m_x_coord; }

        /**
         * (Y Coord * 0x100) + 0x80 (sort of a fixed point value)
         */
        uint32_t y_coord() const { return m_y_coord; }
        uint32_t type_id() const { return m_type_id; }

        /**
         * Condition of a structure in a range [0..100]
         */
        uint16_t health() const { return m_health; }

        /**
         * Value in a range [1..16] points to a fraction this structure belongs
         */
        uint32_t fraction_id() const { return m_fraction_id; }
        uint16_t id() const { return m_id; }
        bridge_info_t* bridge_details() const { return m_bridge_details; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::structures_sec_t* _parent() const { return m__parent; }
    };

    class unit_entry_t : public kaitai::kstruct {

    public:

        unit_entry_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::units_sec_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~unit_entry_t();

    private:
        uint32_t m_x_coord;
        uint32_t m_y_coord;
        uint16_t m_type_id;
        uint16_t m_face_id;
        uint32_t m_special_flags;
        uint32_t m_server_id;
        uint32_t m_fraction_id;
        uint32_t m_sack_id;
        uint32_t m_view_angle;
        double m_unknown_double_0;
        double m_unknown_double_1;
        double m_unknown_double_2;
        double m_unknown_double_3;
        uint16_t m_unit_id;
        uint32_t m_group_id;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::units_sec_t* m__parent;

    public:

        /**
         * (X Coord * 0x100) + 0x80 (sort of a fixed point value)
         */
        uint32_t x_coord() const { return m_x_coord; }

        /**
         * (Y Coord * 0x100) + 0x80 (sort of a fixed point value)
         */
        uint32_t y_coord() const { return m_y_coord; }

        /**
         * In case of Server Id == 0 this id points to a Monster Kind, otherwise
         * it is part of a composite identifier in humans declaration
         */
        uint16_t type_id() const { return m_type_id; }

        /**
         * This identifier points to a portrait of a unit, and, in case of a
         * monster, additionally describes its level (from 1 to 4)
         */
        uint16_t face_id() const { return m_face_id; }

        /**
         * This value contains set of flags such as Is VIP(zero bit),
         * Is Quest For Intercept(first bit), Is Quest For Escort(second bit),
         * Is No XP For Kill(third bit). This knowledge was directly adapted
         * from the ALM format for the Allods II and should be tested.
         */
        uint32_t special_flags() const { return m_special_flags; }

        /**
         * Helps to find a right entry in a humans declaration
         */
        uint32_t server_id() const { return m_server_id; }

        /**
         * Value in a range [1..16] points to a fraction this unit belongs
         */
        uint32_t fraction_id() const { return m_fraction_id; }

        /**
         * If not storing a zero value, points to an identifier of a sacks section
         * entry, where the connected Sack(think about it as of a units inventory)
         * described.
         */
        uint32_t sack_id() const { return m_sack_id; }

        /**
         * Storing value in a range [0..15] with a meaning of angle of view of a
         * unit(where it looks at map start).
         * 
         * Angle In Degrees = View Angle * 22.5f
         */
        uint32_t view_angle() const { return m_view_angle; }
        double unknown_double_0() const { return m_unknown_double_0; }
        double unknown_double_1() const { return m_unknown_double_1; }
        double unknown_double_2() const { return m_unknown_double_2; }
        double unknown_double_3() const { return m_unknown_double_3; }

        /**
         * Identifier of a unit entry in units section
         */
        uint16_t unit_id() const { return m_unit_id; }

        /**
         * Giving the knowledge for which group this unit belongs
         */
        uint32_t group_id() const { return m_group_id; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::units_sec_t* _parent() const { return m__parent; }
    };

    class fraction_entry_t : public kaitai::kstruct {

    public:

        fraction_entry_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::fractions_sec_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~fraction_entry_t();

    private:
        uint32_t m_color_id;
        uint32_t m_flags;
        uint32_t m_money;
        std::string m_name;
        std::vector<uint16_t>* m_diplomacy_states;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::fractions_sec_t* m__parent;

    public:
        uint32_t color_id() const { return m_color_id; }

        /**
         * Zero bit => Is Computer, First bit => Is Quest For Kill
         */
        uint32_t flags() const { return m_flags; }
        uint32_t money() const { return m_money; }

        /**
         * Player name. Ends with terminal zero
         */
        std::string name() const { return m_name; }
        std::vector<uint16_t>* diplomacy_states() const { return m_diplomacy_states; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::fractions_sec_t* _parent() const { return m__parent; }
    };

    class tiles_sec_t : public kaitai::kstruct {

    public:

        tiles_sec_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::alm_section_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~tiles_sec_t();

    private:
        std::vector<tile_entry_t*>* m_tiles;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::alm_section_t* m__parent;
        std::vector<std::string>* m__raw_tiles;
        std::vector<kaitai::kstream*>* m__io__raw_tiles;

    public:
        std::vector<tile_entry_t*>* tiles() const { return m_tiles; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::alm_section_t* _parent() const { return m__parent; }
        std::vector<std::string>* _raw_tiles() const { return m__raw_tiles; }
        std::vector<kaitai::kstream*>* _io__raw_tiles() const { return m__io__raw_tiles; }
    };

    class item_entry_t : public kaitai::kstruct {

    public:

        item_entry_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::sack_entry_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~item_entry_t();

    private:
        uint32_t m_item_id;
        uint16_t m_wielded;
        uint32_t m_effect_id;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::sack_entry_t* m__parent;

    public:
        uint32_t item_id() const { return m_item_id; }
        uint16_t wielded() const { return m_wielded; }
        uint32_t effect_id() const { return m_effect_id; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::sack_entry_t* _parent() const { return m__parent; }
    };

    class sack_entry_t : public kaitai::kstruct {

    public:

        sack_entry_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::sacks_sec_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~sack_entry_t();

    private:
        uint32_t m_item_count;
        uint32_t m_unit_id;
        uint32_t m_x_coord;
        uint32_t m_y_coord;
        uint32_t m_money;
        std::vector<item_entry_t*>* m_items;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::sacks_sec_t* m__parent;

    public:
        uint32_t item_count() const { return m_item_count; }

        /**
         * Id of a Unit connected to this sack
         */
        uint32_t unit_id() const { return m_unit_id; }

        /**
         * (X Coord * 0x100) + 0x80 (sort of a fixed point value)
         */
        uint32_t x_coord() const { return m_x_coord; }

        /**
         * (Y Coord * 0x100) + 0x80 (sort of a fixed point value)
         */
        uint32_t y_coord() const { return m_y_coord; }
        uint32_t money() const { return m_money; }
        std::vector<item_entry_t*>* items() const { return m_items; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::sacks_sec_t* _parent() const { return m__parent; }
    };

    class effects_sec_t : public kaitai::kstruct {

    public:

        effects_sec_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::alm_section_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~effects_sec_t();

    private:
        uint32_t m_effect_count;
        std::vector<effect_entry_t*>* m_entries;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::alm_section_t* m__parent;

    public:
        uint32_t effect_count() const { return m_effect_count; }
        std::vector<effect_entry_t*>* entries() const { return m_entries; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::alm_section_t* _parent() const { return m__parent; }
    };

    class effect_entry_t : public kaitai::kstruct {

    public:

        effect_entry_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::effects_sec_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~effect_entry_t();

    private:
        uint32_t m_corrupt_effect_id;
        uint32_t m_trap_x;
        uint32_t m_trap_y;
        uint16_t m_flags_or_magic_sphere;
        uint64_t m_service_data;
        uint32_t m_modifier_count;
        std::vector<effect_modifier_t*>* m_modifiers;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::effects_sec_t* m__parent;

    public:

        /**
         * Not used. The real Effect Id is just order number in a table
         */
        uint32_t corrupt_effect_id() const { return m_corrupt_effect_id; }
        uint32_t trap_x() const { return m_trap_x; }
        uint32_t trap_y() const { return m_trap_y; }

        /**
         * For flags it's Zero bit => From Structure, First Bit => To Unit
         */
        uint16_t flags_or_magic_sphere() const { return m_flags_or_magic_sphere; }
        uint64_t service_data() const { return m_service_data; }
        uint32_t modifier_count() const { return m_modifier_count; }
        std::vector<effect_modifier_t*>* modifiers() const { return m_modifiers; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::effects_sec_t* _parent() const { return m__parent; }
    };

    class units_sec_t : public kaitai::kstruct {

    public:

        units_sec_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::alm_section_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~units_sec_t();

    private:
        std::vector<unit_entry_t*>* m_units;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::alm_section_t* m__parent;

    public:
        std::vector<unit_entry_t*>* units() const { return m_units; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::alm_section_t* _parent() const { return m__parent; }
    };

    class tile_entry_t : public kaitai::kstruct {

    public:

        tile_entry_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::tiles_sec_t* p__parent = 0, rage_of_mages_1_alm_t* p__root = 0);

    private:
        void _read();

    public:
        ~tile_entry_t();

    private:
        uint16_t m_tile_id;
        rage_of_mages_1_alm_t* m__root;
        rage_of_mages_1_alm_t::tiles_sec_t* m__parent;

    public:

        /**
         * Tile Id is, in fact, a composite identifier, which consists of
         * terrainId, tileColumnId, and tileRowId. In addition, it also
         * contains a passability flag.
         * 
         * bool IsPassable   => (((tile_id & 0xFF00) / 0x100) & 0x20) != 0;
         * byte TerrainId    => (byte) (((tile_id & 0xFF00) / 0x100) & 0x03);
         * byte TileColumnId => (byte) ((tile_id & 0x00F0) / 0x10);
         * byte TileRowId    => (byte) Math.Min(tile_id & 0x0F, TerrainId != 2 ? 13 : 7);
         */
        uint16_t tile_id() const { return m_tile_id; }
        rage_of_mages_1_alm_t* _root() const { return m__root; }
        rage_of_mages_1_alm_t::tiles_sec_t* _parent() const { return m__parent; }
    };

private:
    alm_header_t* m_alm_header;
    section_header_t* m_header;
    general_map_info_sec_t* m_general_map_info;
    std::vector<alm_section_t*>* m_sections;
    rage_of_mages_1_alm_t* m__root;
    kaitai::kstruct* m__parent;
    std::string m__raw_alm_header;
    kaitai::kstream* m__io__raw_alm_header;
    std::string m__raw_header;
    kaitai::kstream* m__io__raw_header;
    std::string m__raw_general_map_info;
    kaitai::kstream* m__io__raw_general_map_info;

public:
    alm_header_t* alm_header() const { return m_alm_header; }
    section_header_t* header() const { return m_header; }
    general_map_info_sec_t* general_map_info() const { return m_general_map_info; }
    std::vector<alm_section_t*>* sections() const { return m_sections; }
    rage_of_mages_1_alm_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
    std::string _raw_alm_header() const { return m__raw_alm_header; }
    kaitai::kstream* _io__raw_alm_header() const { return m__io__raw_alm_header; }
    std::string _raw_header() const { return m__raw_header; }
    kaitai::kstream* _io__raw_header() const { return m__io__raw_header; }
    std::string _raw_general_map_info() const { return m__raw_general_map_info; }
    kaitai::kstream* _io__raw_general_map_info() const { return m__io__raw_general_map_info; }
};

#endif  // RAGE_OF_MAGES_1_ALM_H_
