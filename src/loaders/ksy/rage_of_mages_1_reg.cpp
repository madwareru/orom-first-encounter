// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include <loaders/ksy/rage_of_mages_1_reg.h>

rage_of_mages_1_reg_t::rage_of_mages_1_reg_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, rage_of_mages_1_reg_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    f_nodes = false;
    _read();
}

void rage_of_mages_1_reg_t::_read() {
    m_signature = m__io->ensure_fixed_contents(std::string("\x26\x59\x41\x31", 4));
    m_registry_header = new root_registry_header_t_t(m__io, this, m__root);
}

rage_of_mages_1_reg_t::~rage_of_mages_1_reg_t() {
    delete m_registry_header;
    if (f_nodes) {
        delete m__io__raw_nodes;
        delete m_nodes;
    }
}

rage_of_mages_1_reg_t::registry_header_list_t::registry_header_list_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, rage_of_mages_1_reg_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_reg_t::registry_header_list_t::_read() {
    m__raw_header = new std::vector<std::string>();
    m__io__raw_header = new std::vector<kaitai::kstream*>();
    m_header = new std::vector<registry_header_t*>();
    {
        int i = 0;
        while (!m__io->is_eof()) {
            m__raw_header->push_back(m__io->read_bytes(32));
            kaitai::kstream* io__raw_header = new kaitai::kstream(m__raw_header->at(m__raw_header->size() - 1));
            m__io__raw_header->push_back(io__raw_header);
            m_header->push_back(new registry_header_t(io__raw_header, this, m__root));
            i++;
        }
    }
}

rage_of_mages_1_reg_t::registry_header_list_t::~registry_header_list_t() {
    delete m__raw_header;
    for (std::vector<kaitai::kstream*>::iterator it = m__io__raw_header->begin(); it != m__io__raw_header->end(); ++it) {
        delete *it;
    }
    delete m__io__raw_header;
    for (std::vector<registry_header_t*>::iterator it = m_header->begin(); it != m_header->end(); ++it) {
        delete *it;
    }
    delete m_header;
}

rage_of_mages_1_reg_t::directory_entry_t::directory_entry_t(kaitai::kstream* p__io, rage_of_mages_1_reg_t::registry_header_t* p__parent, rage_of_mages_1_reg_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_value = false;
    _read();
}

void rage_of_mages_1_reg_t::directory_entry_t::_read() {
    m_e_offset = m__io->read_u4le();
    m_e_count = m__io->read_u4le();
}

rage_of_mages_1_reg_t::directory_entry_t::~directory_entry_t() {
    if (f_value) {
        delete m__io__raw_value;
        delete m_value;
    }
}

rage_of_mages_1_reg_t::registry_header_list_t* rage_of_mages_1_reg_t::directory_entry_t::value() {
    if (f_value)
        return m_value;
    kaitai::kstream *io = _root()->_io();
    std::streampos _pos = io->pos();
    io->seek((24 + (32 * e_offset())));
    m__raw_value = io->read_bytes((e_count() * 32));
    m__io__raw_value = new kaitai::kstream(m__raw_value);
    m_value = new registry_header_list_t(m__io__raw_value, this, m__root);
    io->seek(_pos);
    f_value = true;
    return m_value;
}

rage_of_mages_1_reg_t::byte_entry_t::byte_entry_t(kaitai::kstream* p__io, rage_of_mages_1_reg_t::registry_header_t* p__parent, rage_of_mages_1_reg_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_reg_t::byte_entry_t::_read() {
    m_value = m__io->read_u1();
}

rage_of_mages_1_reg_t::byte_entry_t::~byte_entry_t() {
}

rage_of_mages_1_reg_t::string_entry_t::string_entry_t(kaitai::kstream* p__io, rage_of_mages_1_reg_t::registry_header_t* p__parent, rage_of_mages_1_reg_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_value = false;
    _read();
}

void rage_of_mages_1_reg_t::string_entry_t::_read() {
    m_e_offset = m__io->read_u4le();
    m_e_count = m__io->read_u4le();
}

rage_of_mages_1_reg_t::string_entry_t::~string_entry_t() {
    if (f_value) {
    }
}

std::string rage_of_mages_1_reg_t::string_entry_t::value() {
    if (f_value)
        return m_value;
    kaitai::kstream *io = _root()->_io();
    std::streampos _pos = io->pos();
    io->seek((_root()->registry_header()->data_origin() + e_offset()));
    m_value = kaitai::kstream::bytes_to_str(kaitai::kstream::bytes_terminate(io->read_bytes(e_count()), 0, false), std::string("IBM866"));
    io->seek(_pos);
    f_value = true;
    return m_value;
}

rage_of_mages_1_reg_t::registry_header_t::registry_header_t(kaitai::kstream* p__io, rage_of_mages_1_reg_t::registry_header_list_t* p__parent, rage_of_mages_1_reg_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_e_type = false;
    _read();
}

void rage_of_mages_1_reg_t::registry_header_t::_read() {
    m_junk = m__io->read_u4le();
    switch (e_type()) {
    case REGISTRY_TYPE_E_FLOAT: {
        m__raw_value = m__io->read_bytes(8);
        m__io__raw_value = new kaitai::kstream(m__raw_value);
        m_value = new float_entry_t(m__io__raw_value, this, m__root);
        break;
    }
    case REGISTRY_TYPE_E_INT: {
        m__raw_value = m__io->read_bytes(8);
        m__io__raw_value = new kaitai::kstream(m__raw_value);
        m_value = new int_entry_t(m__io__raw_value, this, m__root);
        break;
    }
    case REGISTRY_TYPE_E_STRING: {
        m__raw_value = m__io->read_bytes(8);
        m__io__raw_value = new kaitai::kstream(m__raw_value);
        m_value = new string_entry_t(m__io__raw_value, this, m__root);
        break;
    }
    case REGISTRY_TYPE_E_DIRECTORY: {
        m__raw_value = m__io->read_bytes(8);
        m__io__raw_value = new kaitai::kstream(m__raw_value);
        m_value = new directory_entry_t(m__io__raw_value, this, m__root);
        break;
    }
    case REGISTRY_TYPE_E_INT_ARRAY: {
        m__raw_value = m__io->read_bytes(8);
        m__io__raw_value = new kaitai::kstream(m__raw_value);
        m_value = new int_array_entry_t(m__io__raw_value, this, m__root);
        break;
    }
    default: {
        m__raw_value = m__io->read_bytes(8);
        m__io__raw_value = new kaitai::kstream(m__raw_value);
        m_value = new byte_entry_t(m__io__raw_value, this, m__root);
        break;
    }
    }
    m_typ = m__io->read_u4le();
    m_name = kaitai::kstream::bytes_to_str(kaitai::kstream::bytes_terminate(m__io->read_bytes(16), 0, false), std::string("IBM866"));
}

rage_of_mages_1_reg_t::registry_header_t::~registry_header_t() {
    delete m__io__raw_value;
    delete m_value;
    if (f_e_type) {
    }
}

rage_of_mages_1_reg_t::registry_type_e_t rage_of_mages_1_reg_t::registry_header_t::e_type() {
    if (f_e_type)
        return m_e_type;
    std::streampos _pos = m__io->pos();
    m__io->seek(12);
    m_e_type = static_cast<rage_of_mages_1_reg_t::registry_type_e_t>(m__io->read_u4le());
    m__io->seek(_pos);
    f_e_type = true;
    return m_e_type;
}

rage_of_mages_1_reg_t::int_array_entry_t::int_array_entry_t(kaitai::kstream* p__io, rage_of_mages_1_reg_t::registry_header_t* p__parent, rage_of_mages_1_reg_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_value = false;
    _read();
}

void rage_of_mages_1_reg_t::int_array_entry_t::_read() {
    m_e_offset = m__io->read_u4le();
    m_e_size = m__io->read_u4le();
}

rage_of_mages_1_reg_t::int_array_entry_t::~int_array_entry_t() {
    if (f_value) {
        delete m_value;
    }
}

std::vector<int32_t>* rage_of_mages_1_reg_t::int_array_entry_t::value() {
    if (f_value)
        return m_value;
    kaitai::kstream *io = _root()->_io();
    std::streampos _pos = io->pos();
    io->seek((_root()->registry_header()->data_origin() + e_offset()));
    int l_value = (e_size() / 4);
    m_value = new std::vector<int32_t>();
    m_value->reserve(l_value);
    for (int i = 0; i < l_value; i++) {
        m_value->push_back(io->read_s4le());
    }
    io->seek(_pos);
    f_value = true;
    return m_value;
}

rage_of_mages_1_reg_t::int_entry_t::int_entry_t(kaitai::kstream* p__io, rage_of_mages_1_reg_t::registry_header_t* p__parent, rage_of_mages_1_reg_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_reg_t::int_entry_t::_read() {
    m_value = m__io->read_s4le();
}

rage_of_mages_1_reg_t::int_entry_t::~int_entry_t() {
}

rage_of_mages_1_reg_t::float_entry_t::float_entry_t(kaitai::kstream* p__io, rage_of_mages_1_reg_t::registry_header_t* p__parent, rage_of_mages_1_reg_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_reg_t::float_entry_t::_read() {
    m_value = m__io->read_f8le();
}

rage_of_mages_1_reg_t::float_entry_t::~float_entry_t() {
}

rage_of_mages_1_reg_t::root_registry_header_t_t::root_registry_header_t_t(kaitai::kstream* p__io, rage_of_mages_1_reg_t* p__parent, rage_of_mages_1_reg_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_data_origin = false;
    _read();
}

void rage_of_mages_1_reg_t::root_registry_header_t_t::_read() {
    m_root_offset = m__io->read_u4le();
    m_root_size = m__io->read_u4le();
    m_registry_flags = m__io->read_u4le();
    m_registry_eat_size = m__io->read_u4le();
    m_junk = m__io->read_u4le();
}

rage_of_mages_1_reg_t::root_registry_header_t_t::~root_registry_header_t_t() {
}

int32_t rage_of_mages_1_reg_t::root_registry_header_t_t::data_origin() {
    if (f_data_origin)
        return m_data_origin;
    m_data_origin = (28 + (32 * registry_eat_size()));
    f_data_origin = true;
    return m_data_origin;
}

rage_of_mages_1_reg_t::registry_header_list_t* rage_of_mages_1_reg_t::nodes() {
    if (f_nodes)
        return m_nodes;
    std::streampos _pos = m__io->pos();
    m__io->seek((24 + (32 * registry_header()->root_offset())));
    m__raw_nodes = m__io->read_bytes((registry_header()->root_size() * 32));
    m__io__raw_nodes = new kaitai::kstream(m__raw_nodes);
    m_nodes = new registry_header_list_t(m__io__raw_nodes, this, m__root);
    m__io->seek(_pos);
    f_nodes = true;
    return m_nodes;
}
