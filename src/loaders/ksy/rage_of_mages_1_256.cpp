// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include <loaders/ksy/rage_of_mages_1_256.h>

rage_of_mages_1_256_t::rage_of_mages_1_256_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, rage_of_mages_1_256_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    f_sprite_count_internal = false;
    f_sprite_count = false;
    f_has_palette = false;
    _read();
}

void rage_of_mages_1_256_t::_read() {
    n_inner_palette = true;
    if (has_palette() != 0) {
        n_inner_palette = false;
        int l_inner_palette = 256;
        m_inner_palette = new std::vector<uint32_t>();
        m_inner_palette->reserve(l_inner_palette);
        for (int i = 0; i < l_inner_palette; i++) {
            m_inner_palette->push_back(m__io->read_u4le());
        }
    }
    int l_sprite_records = sprite_count();
    m_sprite_records = new std::vector<sprite_record_t*>();
    m_sprite_records->reserve(l_sprite_records);
    for (int i = 0; i < l_sprite_records; i++) {
        m_sprite_records->push_back(new sprite_record_t(m__io, this, m__root));
    }
}

rage_of_mages_1_256_t::~rage_of_mages_1_256_t() {
    if (!n_inner_palette) {
        delete m_inner_palette;
    }
    for (std::vector<sprite_record_t*>::iterator it = m_sprite_records->begin(); it != m_sprite_records->end(); ++it) {
        delete *it;
    }
    delete m_sprite_records;
    if (f_sprite_count_internal) {
    }
}

rage_of_mages_1_256_t::sprite_record_t::sprite_record_t(kaitai::kstream* p__io, rage_of_mages_1_256_t* p__parent, rage_of_mages_1_256_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rage_of_mages_1_256_t::sprite_record_t::_read() {
    m_width = m__io->read_u4le();
    m_height = m__io->read_u4le();
    m_data_size = m__io->read_u4le();
    m_data = m__io->read_bytes(data_size());
}

rage_of_mages_1_256_t::sprite_record_t::~sprite_record_t() {
}

uint32_t rage_of_mages_1_256_t::sprite_count_internal() {
    if (f_sprite_count_internal)
        return m_sprite_count_internal;
    std::streampos _pos = m__io->pos();
    m__io->seek((_io()->size() - 4));
    m_sprite_count_internal = m__io->read_u4le();
    m__io->seek(_pos);
    f_sprite_count_internal = true;
    return m_sprite_count_internal;
}

int32_t rage_of_mages_1_256_t::sprite_count() {
    if (f_sprite_count)
        return m_sprite_count;
    m_sprite_count = (sprite_count_internal() & 2147483647);
    f_sprite_count = true;
    return m_sprite_count;
}

int32_t rage_of_mages_1_256_t::has_palette() {
    if (f_has_palette)
        return m_has_palette;
    m_has_palette = (sprite_count_internal() & 2147483648);
    f_has_palette = true;
    return m_has_palette;
}
