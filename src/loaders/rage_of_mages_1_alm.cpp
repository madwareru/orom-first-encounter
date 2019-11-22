// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "rage_of_mages_1_alm.h"



rage_of_mages_1_alm_t::rage_of_mages_1_alm_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    _read();
}

void rage_of_mages_1_alm_t::_read() {
    m__raw_alm_header = m__io->read_bytes(20);
    m__io__raw_alm_header = new kaitai::kstream(m__raw_alm_header);
    m_alm_header = new alm_header_t(m__io__raw_alm_header, this, m__root);
    m__raw_header = m__io->read_bytes(20);
    m__io__raw_header = new kaitai::kstream(m__raw_header);
    m_header = new section_header_t(m__io__raw_header, this, m__root);
    m__raw_general_map_info = m__io->read_bytes(header()->data_size());
    m__io__raw_general_map_info = new kaitai::kstream(m__raw_general_map_info);
    m_general_map_info = new general_map_info_sec_t(m__io__raw_general_map_info, this, m__root);
    int l_sections = (alm_header()->section_count() - 1);
    m_sections = new std::vector<alm_section_t*>();
    m_sections->reserve(l_sections);
    for (int i = 0; i < l_sections; i++) {
        m_sections->push_back(new alm_section_t(m__io, this, m__root));
    }
}

rage_of_mages_1_alm_t::~rage_of_mages_1_alm_t() {
    delete m__io__raw_alm_header;
    delete m_alm_header;
    delete m__io__raw_header;
    delete m_header;
    delete m__io__raw_general_map_info;
    delete m_general_map_info;
    for (std::vector<alm_section_t*>::iterator it = m_sections->begin(); it != m_sections->end(); ++it) {
        delete *it;
    }
    delete m_sections;
}

rage_of_mages_1_alm_t::alm_section_t::alm_section_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::alm_section_t::_read() {
    m__raw_header = m__io->read_bytes(20);
    m__io__raw_header = new kaitai::kstream(m__raw_header);
    m_header = new section_header_t(m__io__raw_header, this, m__root);
    n_body = true;
    switch (header()->section_kind()) {
    case SECTION_KIND_E_TILES: {
        n_body = false;
        m__raw_body = m__io->read_bytes(header()->data_size());
        m__io__raw_body = new kaitai::kstream(m__raw_body);
        m_body = new tiles_sec_t(m__io__raw_body, this, m__root);
        break;
    }
    case SECTION_KIND_E_FRACTIONS: {
        n_body = false;
        m__raw_body = m__io->read_bytes(header()->data_size());
        m__io__raw_body = new kaitai::kstream(m__raw_body);
        m_body = new fractions_sec_t(m__io__raw_body, this, m__root);
        break;
    }
    case SECTION_KIND_E_SACKS: {
        n_body = false;
        m__raw_body = m__io->read_bytes(header()->data_size());
        m__io__raw_body = new kaitai::kstream(m__raw_body);
        m_body = new sacks_sec_t(m__io__raw_body, this, m__root);
        break;
    }
    case SECTION_KIND_E_EFFECTS: {
        n_body = false;
        m__raw_body = m__io->read_bytes(header()->data_size());
        m__io__raw_body = new kaitai::kstream(m__raw_body);
        m_body = new effects_sec_t(m__io__raw_body, this, m__root);
        break;
    }
    case SECTION_KIND_E_MAP_OBJECTS: {
        n_body = false;
        m__raw_body = m__io->read_bytes(header()->data_size());
        m__io__raw_body = new kaitai::kstream(m__raw_body);
        m_body = new map_objects_sec_t(m__io__raw_body, this, m__root);
        break;
    }
    case SECTION_KIND_E_STRUCTURES: {
        n_body = false;
        m__raw_body = m__io->read_bytes(header()->data_size());
        m__io__raw_body = new kaitai::kstream(m__raw_body);
        m_body = new structures_sec_t(m__io__raw_body, this, m__root);
        break;
    }
    case SECTION_KIND_E_HEIGHT_MAP: {
        n_body = false;
        m__raw_body = m__io->read_bytes(header()->data_size());
        m__io__raw_body = new kaitai::kstream(m__raw_body);
        m_body = new height_map_sec_t(m__io__raw_body, this, m__root);
        break;
    }
    case SECTION_KIND_E_UNITS: {
        n_body = false;
        m__raw_body = m__io->read_bytes(header()->data_size());
        m__io__raw_body = new kaitai::kstream(m__raw_body);
        m_body = new units_sec_t(m__io__raw_body, this, m__root);
        break;
    }
    case SECTION_KIND_E_TRIGGERS: {
        n_body = false;
        m__raw_body = m__io->read_bytes(header()->data_size());
        m__io__raw_body = new kaitai::kstream(m__raw_body);
        m_body = new triggers_sec_t(m__io__raw_body, this, m__root);
        break;
    }
    default: {
        m__raw_body = m__io->read_bytes(header()->data_size());
        break;
    }
    }
}

rage_of_mages_1_alm_t::alm_section_t::~alm_section_t() {
    delete m__io__raw_header;
    delete m_header;
    if (!n_body) {
        delete m__io__raw_body;
        delete m_body;
    }
}

rage_of_mages_1_alm_t::trigger_entry_t::trigger_entry_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::triggers_sec_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::trigger_entry_t::_read() {
    m_name = kaitai::kstream::bytes_to_str(kaitai::kstream::bytes_terminate(m__io->read_bytes(128), 0, false), std::string("ASCII"));
    int l_check_identifiers = 6;
    m_check_identifiers = new std::vector<uint32_t>();
    m_check_identifiers->reserve(l_check_identifiers);
    for (int i = 0; i < l_check_identifiers; i++) {
        m_check_identifiers->push_back(m__io->read_u4le());
    }
    int l_instance_identifiers = 4;
    m_instance_identifiers = new std::vector<uint32_t>();
    m_instance_identifiers->reserve(l_instance_identifiers);
    for (int i = 0; i < l_instance_identifiers; i++) {
        m_instance_identifiers->push_back(m__io->read_u4le());
    }
    m_check_01_operator = static_cast<rage_of_mages_1_alm_t::check_operator_t>(m__io->read_u4le());
    m_check_23_operator = static_cast<rage_of_mages_1_alm_t::check_operator_t>(m__io->read_u4le());
    m_check_45_operator = static_cast<rage_of_mages_1_alm_t::check_operator_t>(m__io->read_u4le());
    m_run_once_flag = m__io->read_u4le();
}

rage_of_mages_1_alm_t::trigger_entry_t::~trigger_entry_t() {
    delete m_check_identifiers;
    delete m_instance_identifiers;
}

rage_of_mages_1_alm_t::map_objects_sec_t::map_objects_sec_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::alm_section_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::map_objects_sec_t::_read() {
    int l_objects = (_root()->general_map_info()->width() * _root()->general_map_info()->height());
    m_objects = new std::vector<uint8_t>();
    m_objects->reserve(l_objects);
    for (int i = 0; i < l_objects; i++) {
        m_objects->push_back(m__io->read_u1());
    }
}

rage_of_mages_1_alm_t::map_objects_sec_t::~map_objects_sec_t() {
    delete m_objects;
}

rage_of_mages_1_alm_t::instance_entry_t::instance_entry_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::triggers_sec_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::instance_entry_t::_read() {
    m_name = kaitai::kstream::bytes_to_str(kaitai::kstream::bytes_terminate(m__io->read_bytes(64), 0, false), std::string("ASCII"));
    m_type = static_cast<rage_of_mages_1_alm_t::instance_type_t>(m__io->read_u4le());
    m_id = m__io->read_u4le();
    m_execute_once_flag = m__io->read_u4le();
    int l_argument_values = 10;
    m_argument_values = new std::vector<uint32_t>();
    m_argument_values->reserve(l_argument_values);
    for (int i = 0; i < l_argument_values; i++) {
        m_argument_values->push_back(m__io->read_u4le());
    }
    int l_argument_types = 10;
    m_argument_types = new std::vector<argument_type_t>();
    m_argument_types->reserve(l_argument_types);
    for (int i = 0; i < l_argument_types; i++) {
        m_argument_types->push_back(static_cast<rage_of_mages_1_alm_t::argument_type_t>(m__io->read_u4le()));
    }
    int l_argument_names = 10;
    m_argument_names = new std::vector<std::string>();
    m_argument_names->reserve(l_argument_names);
    for (int i = 0; i < l_argument_names; i++) {
        m_argument_names->push_back(kaitai::kstream::bytes_to_str(kaitai::kstream::bytes_terminate(m__io->read_bytes(64), 0, false), std::string("ASCII")));
    }
}

rage_of_mages_1_alm_t::instance_entry_t::~instance_entry_t() {
    delete m_argument_values;
    delete m_argument_types;
    delete m_argument_names;
}

rage_of_mages_1_alm_t::structures_sec_t::structures_sec_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::alm_section_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::structures_sec_t::_read() {
    int l_structures = _root()->general_map_info()->structure_count();
    m_structures = new std::vector<structure_entry_t*>();
    m_structures->reserve(l_structures);
    for (int i = 0; i < l_structures; i++) {
        m_structures->push_back(new structure_entry_t(m__io, this, m__root));
    }
}

rage_of_mages_1_alm_t::structures_sec_t::~structures_sec_t() {
    for (std::vector<structure_entry_t*>::iterator it = m_structures->begin(); it != m_structures->end(); ++it) {
        delete *it;
    }
    delete m_structures;
}

rage_of_mages_1_alm_t::sacks_sec_t::sacks_sec_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::alm_section_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::sacks_sec_t::_read() {
    int l_sacks = _root()->general_map_info()->sack_count();
    m_sacks = new std::vector<sack_entry_t*>();
    m_sacks->reserve(l_sacks);
    for (int i = 0; i < l_sacks; i++) {
        m_sacks->push_back(new sack_entry_t(m__io, this, m__root));
    }
}

rage_of_mages_1_alm_t::sacks_sec_t::~sacks_sec_t() {
    for (std::vector<sack_entry_t*>::iterator it = m_sacks->begin(); it != m_sacks->end(); ++it) {
        delete *it;
    }
    delete m_sacks;
}

rage_of_mages_1_alm_t::general_map_info_sec_t::general_map_info_sec_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::general_map_info_sec_t::_read() {
    m_width = m__io->read_u4le();
    m_height = m__io->read_u4le();
    m_negative_sun_angle = m__io->read_f4le();
    m_time_in_minutes = m__io->read_u4le();
    m_darkness = m__io->read_u4le();
    m_contrast = m__io->read_u4le();
    m_use_tiles = m__io->read_u4le();
    m_fraction_count = m__io->read_u4le();
    m_structure_count = m__io->read_u4le();
    m_unit_count = m__io->read_u4le();
    m_logic_count = m__io->read_u4le();
    m_sack_count = m__io->read_u4le();
}

rage_of_mages_1_alm_t::general_map_info_sec_t::~general_map_info_sec_t() {
}

rage_of_mages_1_alm_t::fractions_sec_t::fractions_sec_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::alm_section_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::fractions_sec_t::_read() {
    int l_fractions = _root()->general_map_info()->fraction_count();
    m_fractions = new std::vector<fraction_entry_t*>();
    m_fractions->reserve(l_fractions);
    for (int i = 0; i < l_fractions; i++) {
        m_fractions->push_back(new fraction_entry_t(m__io, this, m__root));
    }
}

rage_of_mages_1_alm_t::fractions_sec_t::~fractions_sec_t() {
    for (std::vector<fraction_entry_t*>::iterator it = m_fractions->begin(); it != m_fractions->end(); ++it) {
        delete *it;
    }
    delete m_fractions;
}

rage_of_mages_1_alm_t::effect_modifier_t::effect_modifier_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::effect_entry_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::effect_modifier_t::_read() {
    m_modifier_type = m__io->read_u2le();
    m_modifier_value = m__io->read_u4le();
}

rage_of_mages_1_alm_t::effect_modifier_t::~effect_modifier_t() {
}

rage_of_mages_1_alm_t::height_map_sec_t::height_map_sec_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::alm_section_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::height_map_sec_t::_read() {
    int l_heights = (_root()->general_map_info()->width() * _root()->general_map_info()->height());
    m_heights = new std::vector<uint8_t>();
    m_heights->reserve(l_heights);
    for (int i = 0; i < l_heights; i++) {
        m_heights->push_back(m__io->read_u1());
    }
}

rage_of_mages_1_alm_t::height_map_sec_t::~height_map_sec_t() {
    delete m_heights;
}

rage_of_mages_1_alm_t::bridge_info_t::bridge_info_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::structure_entry_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::bridge_info_t::_read() {
    m_width = m__io->read_u4le();
    m_height = m__io->read_u4le();
}

rage_of_mages_1_alm_t::bridge_info_t::~bridge_info_t() {
}

rage_of_mages_1_alm_t::section_header_t::section_header_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::section_header_t::_read() {
    m_some_number = m__io->read_u4le();
    m_header_size = m__io->read_u4le();
    m_data_size = m__io->read_u4le();
    m_section_kind = static_cast<rage_of_mages_1_alm_t::section_kind_e_t>(m__io->read_u4le());
    m_random_seed = m__io->read_u4le();
}

rage_of_mages_1_alm_t::section_header_t::~section_header_t() {
}

rage_of_mages_1_alm_t::check_entry_t::check_entry_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::triggers_sec_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::check_entry_t::_read() {
    m_name = kaitai::kstream::bytes_to_str(kaitai::kstream::bytes_terminate(m__io->read_bytes(64), 0, false), std::string("ASCII"));
    m_type = static_cast<rage_of_mages_1_alm_t::check_type_t>(m__io->read_u4le());
    m_id = m__io->read_u4le();
    m_execute_once_flag = m__io->read_u4le();
    int l_argument_values = 10;
    m_argument_values = new std::vector<uint32_t>();
    m_argument_values->reserve(l_argument_values);
    for (int i = 0; i < l_argument_values; i++) {
        m_argument_values->push_back(m__io->read_u4le());
    }
    int l_argument_types = 10;
    m_argument_types = new std::vector<argument_type_t>();
    m_argument_types->reserve(l_argument_types);
    for (int i = 0; i < l_argument_types; i++) {
        m_argument_types->push_back(static_cast<rage_of_mages_1_alm_t::argument_type_t>(m__io->read_u4le()));
    }
    int l_argument_names = 10;
    m_argument_names = new std::vector<std::string>();
    m_argument_names->reserve(l_argument_names);
    for (int i = 0; i < l_argument_names; i++) {
        m_argument_names->push_back(kaitai::kstream::bytes_to_str(kaitai::kstream::bytes_terminate(m__io->read_bytes(64), 0, false), std::string("ASCII")));
    }
}

rage_of_mages_1_alm_t::check_entry_t::~check_entry_t() {
    delete m_argument_values;
    delete m_argument_types;
    delete m_argument_names;
}

rage_of_mages_1_alm_t::alm_header_t::alm_header_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::alm_header_t::_read() {
    m_magic = m__io->ensure_fixed_contents(std::string("\x4D\x37\x52\x00", 4));
    m_header_size = m__io->read_u4le();
    m_mysterious_size = m__io->read_u4le();
    m_section_count = m__io->read_u4le();
    m_random_seed = m__io->read_u4le();
}

rage_of_mages_1_alm_t::alm_header_t::~alm_header_t() {
}

rage_of_mages_1_alm_t::triggers_sec_t::triggers_sec_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::alm_section_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::triggers_sec_t::_read() {
    m_instance_count = m__io->read_u4le();
    int l_instances = instance_count();
    m_instances = new std::vector<instance_entry_t*>();
    m_instances->reserve(l_instances);
    for (int i = 0; i < l_instances; i++) {
        m_instances->push_back(new instance_entry_t(m__io, this, m__root));
    }
    m_check_count = m__io->read_u4le();
    int l_checks = check_count();
    m_checks = new std::vector<check_entry_t*>();
    m_checks->reserve(l_checks);
    for (int i = 0; i < l_checks; i++) {
        m_checks->push_back(new check_entry_t(m__io, this, m__root));
    }
    m_trigger_count = m__io->read_u4le();
    int l_triggers = trigger_count();
    m_triggers = new std::vector<trigger_entry_t*>();
    m_triggers->reserve(l_triggers);
    for (int i = 0; i < l_triggers; i++) {
        m_triggers->push_back(new trigger_entry_t(m__io, this, m__root));
    }
}

rage_of_mages_1_alm_t::triggers_sec_t::~triggers_sec_t() {
    for (std::vector<instance_entry_t*>::iterator it = m_instances->begin(); it != m_instances->end(); ++it) {
        delete *it;
    }
    delete m_instances;
    for (std::vector<check_entry_t*>::iterator it = m_checks->begin(); it != m_checks->end(); ++it) {
        delete *it;
    }
    delete m_checks;
    for (std::vector<trigger_entry_t*>::iterator it = m_triggers->begin(); it != m_triggers->end(); ++it) {
        delete *it;
    }
    delete m_triggers;
}

rage_of_mages_1_alm_t::structure_entry_t::structure_entry_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::structures_sec_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::structure_entry_t::_read() {
    m_x_coord = m__io->read_u4le();
    m_y_coord = m__io->read_u4le();
    m_type_id = m__io->read_u4le();
    m_health = m__io->read_u2le();
    m_fraction_id = m__io->read_u4le();
    m_id = m__io->read_u2le();
    n_bridge_details = true;
    if (type_id() == 33) {
        n_bridge_details = false;
        m_bridge_details = new bridge_info_t(m__io, this, m__root);
    }
}

rage_of_mages_1_alm_t::structure_entry_t::~structure_entry_t() {
    if (!n_bridge_details) {
        delete m_bridge_details;
    }
}

rage_of_mages_1_alm_t::unit_entry_t::unit_entry_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::units_sec_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::unit_entry_t::_read() {
    m_x_coord = m__io->read_u4le();
    m_y_coord = m__io->read_u4le();
    m_type_id = m__io->read_u2le();
    m_face_id = m__io->read_u2le();
    m_special_flags = m__io->read_u4le();
    m_server_id = m__io->read_u4le();
    m_fraction_id = m__io->read_u4le();
    m_sack_id = m__io->read_u4le();
    m_view_angle = m__io->read_u4le();
    m_unknown_double_0 = m__io->read_f8le();
    m_unknown_double_1 = m__io->read_f8le();
    m_unknown_double_2 = m__io->read_f8le();
    m_unknown_double_3 = m__io->read_f8le();
    m_unit_id = m__io->read_u2le();
    m_group_id = m__io->read_u4le();
}

rage_of_mages_1_alm_t::unit_entry_t::~unit_entry_t() {
}

rage_of_mages_1_alm_t::fraction_entry_t::fraction_entry_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::fractions_sec_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::fraction_entry_t::_read() {
    m_color_id = m__io->read_u4le();
    m_flags = m__io->read_u4le();
    m_money = m__io->read_u4le();
    m_name = kaitai::kstream::bytes_to_str(kaitai::kstream::bytes_terminate(m__io->read_bytes(32), 0, false), std::string("ASCII"));
    int l_diplomacy_states = 16;
    m_diplomacy_states = new std::vector<uint16_t>();
    m_diplomacy_states->reserve(l_diplomacy_states);
    for (int i = 0; i < l_diplomacy_states; i++) {
        m_diplomacy_states->push_back(m__io->read_u2le());
    }
}

rage_of_mages_1_alm_t::fraction_entry_t::~fraction_entry_t() {
    delete m_diplomacy_states;
}

rage_of_mages_1_alm_t::tiles_sec_t::tiles_sec_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::alm_section_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::tiles_sec_t::_read() {
    int l_tiles = (_root()->general_map_info()->width() * _root()->general_map_info()->height());
    m__raw_tiles = new std::vector<std::string>();
    m__raw_tiles->reserve(l_tiles);
    m__io__raw_tiles = new std::vector<kaitai::kstream*>();
    m__io__raw_tiles->reserve(l_tiles);
    m_tiles = new std::vector<tile_entry_t*>();
    m_tiles->reserve(l_tiles);
    for (int i = 0; i < l_tiles; i++) {
        m__raw_tiles->push_back(m__io->read_bytes(2));
        kaitai::kstream* io__raw_tiles = new kaitai::kstream(m__raw_tiles->at(m__raw_tiles->size() - 1));
        m__io__raw_tiles->push_back(io__raw_tiles);
        m_tiles->push_back(new tile_entry_t(io__raw_tiles, this, m__root));
    }
}

rage_of_mages_1_alm_t::tiles_sec_t::~tiles_sec_t() {
    delete m__raw_tiles;
    for (std::vector<kaitai::kstream*>::iterator it = m__io__raw_tiles->begin(); it != m__io__raw_tiles->end(); ++it) {
        delete *it;
    }
    delete m__io__raw_tiles;
    for (std::vector<tile_entry_t*>::iterator it = m_tiles->begin(); it != m_tiles->end(); ++it) {
        delete *it;
    }
    delete m_tiles;
}

rage_of_mages_1_alm_t::item_entry_t::item_entry_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::sack_entry_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::item_entry_t::_read() {
    m_item_id = m__io->read_u4le();
    m_wielded = m__io->read_u2le();
    m_effect_id = m__io->read_u4le();
}

rage_of_mages_1_alm_t::item_entry_t::~item_entry_t() {
}

rage_of_mages_1_alm_t::sack_entry_t::sack_entry_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::sacks_sec_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::sack_entry_t::_read() {
    m_item_count = m__io->read_u4le();
    m_unit_id = m__io->read_u4le();
    m_x_coord = m__io->read_u4le();
    m_y_coord = m__io->read_u4le();
    m_money = m__io->read_u4le();
    int l_items = item_count();
    m_items = new std::vector<item_entry_t*>();
    m_items->reserve(l_items);
    for (int i = 0; i < l_items; i++) {
        m_items->push_back(new item_entry_t(m__io, this, m__root));
    }
}

rage_of_mages_1_alm_t::sack_entry_t::~sack_entry_t() {
    for (std::vector<item_entry_t*>::iterator it = m_items->begin(); it != m_items->end(); ++it) {
        delete *it;
    }
    delete m_items;
}

rage_of_mages_1_alm_t::effects_sec_t::effects_sec_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::alm_section_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::effects_sec_t::_read() {
    m_effect_count = m__io->read_u4le();
    int l_entries = effect_count();
    m_entries = new std::vector<effect_entry_t*>();
    m_entries->reserve(l_entries);
    for (int i = 0; i < l_entries; i++) {
        m_entries->push_back(new effect_entry_t(m__io, this, m__root));
    }
}

rage_of_mages_1_alm_t::effects_sec_t::~effects_sec_t() {
    for (std::vector<effect_entry_t*>::iterator it = m_entries->begin(); it != m_entries->end(); ++it) {
        delete *it;
    }
    delete m_entries;
}

rage_of_mages_1_alm_t::effect_entry_t::effect_entry_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::effects_sec_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::effect_entry_t::_read() {
    m_corrupt_effect_id = m__io->read_u4le();
    m_trap_x = m__io->read_u4le();
    m_trap_y = m__io->read_u4le();
    m_flags_or_magic_sphere = m__io->read_u2le();
    m_service_data = m__io->read_u8le();
    m_modifier_count = m__io->read_u4le();
    int l_modifiers = modifier_count();
    m_modifiers = new std::vector<effect_modifier_t*>();
    m_modifiers->reserve(l_modifiers);
    for (int i = 0; i < l_modifiers; i++) {
        m_modifiers->push_back(new effect_modifier_t(m__io, this, m__root));
    }
}

rage_of_mages_1_alm_t::effect_entry_t::~effect_entry_t() {
    for (std::vector<effect_modifier_t*>::iterator it = m_modifiers->begin(); it != m_modifiers->end(); ++it) {
        delete *it;
    }
    delete m_modifiers;
}

rage_of_mages_1_alm_t::units_sec_t::units_sec_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::alm_section_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::units_sec_t::_read() {
    int l_units = _root()->general_map_info()->unit_count();
    m_units = new std::vector<unit_entry_t*>();
    m_units->reserve(l_units);
    for (int i = 0; i < l_units; i++) {
        m_units->push_back(new unit_entry_t(m__io, this, m__root));
    }
}

rage_of_mages_1_alm_t::units_sec_t::~units_sec_t() {
    for (std::vector<unit_entry_t*>::iterator it = m_units->begin(); it != m_units->end(); ++it) {
        delete *it;
    }
    delete m_units;
}

rage_of_mages_1_alm_t::tile_entry_t::tile_entry_t(kaitai::kstream* p__io, rage_of_mages_1_alm_t::tiles_sec_t* p__parent, rage_of_mages_1_alm_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_alm_t::tile_entry_t::_read() {
    m_tile_id = m__io->read_u2le();
}

rage_of_mages_1_alm_t::tile_entry_t::~tile_entry_t() {
}
