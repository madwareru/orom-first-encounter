// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include <loaders/ksy/rage_of_mages_1_res.h>

rage_of_mages_1_res_t::rage_of_mages_1_res_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, rage_of_mages_1_res_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    f_nodes = false;
    _read();
}

void rage_of_mages_1_res_t::_read() {
    m_signature = m__io->ensure_fixed_contents(std::string("\x26\x59\x41\x31", 4));
    m_resource_header = new root_resource_header_t_t(m__io, this, m__root);
}

rage_of_mages_1_res_t::~rage_of_mages_1_res_t() {
    delete m_resource_header;
    if (f_nodes) {
        delete m__io__raw_nodes;
        delete m_nodes;
    }
}

rage_of_mages_1_res_t::directory_resource_t::directory_resource_t(kaitai::kstream* p__io, rage_of_mages_1_res_t::resource_header_t* p__parent, rage_of_mages_1_res_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_nodes = false;
    _read();
}

void rage_of_mages_1_res_t::directory_resource_t::_read() {
    m_directory_name = kaitai::kstream::bytes_to_str(kaitai::kstream::bytes_terminate(m__io->read_bytes(16), 0, false), std::string("IBM866"));
}

rage_of_mages_1_res_t::directory_resource_t::~directory_resource_t() {
    if (f_nodes) {
        delete m__io__raw_nodes;
        delete m_nodes;
    }
}

rage_of_mages_1_res_t::resource_header_list_t* rage_of_mages_1_res_t::directory_resource_t::nodes() {
    if (f_nodes)
        return m_nodes;
    kaitai::kstream *io = _root()->_io();
    std::streampos _pos = io->pos();
    io->seek((_root()->resource_header()->fat_offset() + (_parent()->root_offset() * 32)));
    m__raw_nodes = io->read_bytes((_parent()->root_size() * 32));
    m__io__raw_nodes = new kaitai::kstream(m__raw_nodes);
    m_nodes = new resource_header_list_t(m__io__raw_nodes, this, m__root);
    io->seek(_pos);
    f_nodes = true;
    return m_nodes;
}

rage_of_mages_1_res_t::file_resource_t::file_resource_t(kaitai::kstream* p__io, rage_of_mages_1_res_t::resource_header_t* p__parent, rage_of_mages_1_res_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_bytes = false;
    _read();
}

void rage_of_mages_1_res_t::file_resource_t::_read() {
    m_file_name = kaitai::kstream::bytes_to_str(kaitai::kstream::bytes_terminate(m__io->read_bytes(16), 0, false), std::string("IBM866"));
}

rage_of_mages_1_res_t::file_resource_t::~file_resource_t() {
    if (f_bytes) {
    }
}

std::string rage_of_mages_1_res_t::file_resource_t::bytes() {
    if (f_bytes)
        return m_bytes;
    kaitai::kstream *io = _root()->_io();
    std::streampos _pos = io->pos();
    io->seek(_parent()->root_offset());
    m_bytes = io->read_bytes(_parent()->root_size());
    io->seek(_pos);
    f_bytes = true;
    return m_bytes;
}

rage_of_mages_1_res_t::resource_header_t::resource_header_t(kaitai::kstream* p__io, rage_of_mages_1_res_t::resource_header_list_t* p__parent, rage_of_mages_1_res_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_res_t::resource_header_t::_read() {
    m_junk = m__io->read_u4le();
    m_root_offset = m__io->read_u4le();
    m_root_size = m__io->read_u4le();
    m_resource_type = static_cast<rage_of_mages_1_res_t::resource_type_e_t>(m__io->read_u4le());
    n_resource = true;
    switch (resource_type()) {
    case RESOURCE_TYPE_E_FILE: {
        n_resource = false;
        m_resource = new file_resource_t(m__io, this, m__root);
        break;
    }
    case RESOURCE_TYPE_E_DIRECTORY: {
        n_resource = false;
        m_resource = new directory_resource_t(m__io, this, m__root);
        break;
    }
    }
}

rage_of_mages_1_res_t::resource_header_t::~resource_header_t() {
    if (!n_resource) {
        delete m_resource;
    }
}

rage_of_mages_1_res_t::root_resource_header_t_t::root_resource_header_t_t(kaitai::kstream* p__io, rage_of_mages_1_res_t* p__parent, rage_of_mages_1_res_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_res_t::root_resource_header_t_t::_read() {
    m_root_offset = m__io->read_u4le();
    m_root_size = m__io->read_u4le();
    m_resource_flags = m__io->read_u4le();
    m_fat_offset = m__io->read_u4le();
    m_fat_size = m__io->read_u4le();
}

rage_of_mages_1_res_t::root_resource_header_t_t::~root_resource_header_t_t() {
}

rage_of_mages_1_res_t::resource_header_list_t::resource_header_list_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, rage_of_mages_1_res_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_res_t::resource_header_list_t::_read() {
    m__raw_header = new std::vector<std::string>();
    m__io__raw_header = new std::vector<kaitai::kstream*>();
    m_header = new std::vector<resource_header_t*>();
    {
        int i = 0;
        while (!m__io->is_eof()) {
            m__raw_header->push_back(m__io->read_bytes(32));
            kaitai::kstream* io__raw_header = new kaitai::kstream(m__raw_header->at(m__raw_header->size() - 1));
            m__io__raw_header->push_back(io__raw_header);
            m_header->push_back(new resource_header_t(io__raw_header, this, m__root));
            i++;
        }
    }
}

rage_of_mages_1_res_t::resource_header_list_t::~resource_header_list_t() {
    delete m__raw_header;
    for (std::vector<kaitai::kstream*>::iterator it = m__io__raw_header->begin(); it != m__io__raw_header->end(); ++it) {
        delete *it;
    }
    delete m__io__raw_header;
    for (std::vector<resource_header_t*>::iterator it = m_header->begin(); it != m_header->end(); ++it) {
        delete *it;
    }
    delete m_header;
}

rage_of_mages_1_res_t::resource_header_list_t* rage_of_mages_1_res_t::nodes() {
    if (f_nodes)
        return m_nodes;
    std::streampos _pos = m__io->pos();
    m__io->seek((resource_header()->fat_offset() + (_root()->resource_header()->root_offset() * 32)));
    m__raw_nodes = m__io->read_bytes((resource_header()->root_size() * 32));
    m__io__raw_nodes = new kaitai::kstream(m__raw_nodes);
    m_nodes = new resource_header_list_t(m__io__raw_nodes, this, m__root);
    m__io->seek(_pos);
    f_nodes = true;
    return m_nodes;
}
