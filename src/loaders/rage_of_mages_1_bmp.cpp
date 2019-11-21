// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "rage_of_mages_1_bmp.h"



rage_of_mages_1_bmp_t::rage_of_mages_1_bmp_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, rage_of_mages_1_bmp_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    _read();
}

void rage_of_mages_1_bmp_t::_read() {
    m_magic = m__io->ensure_fixed_contents(std::string("\x42\x4D", 2));
    m_unused0 = m__io->read_u4le();
    m_unused1 = m__io->read_u4le();
    m_bfh_pixeldata = m__io->read_u4le();
    m_bi_version = m__io->read_u4le();
    n_data = true;
    if ( ((bi_version() != 12) && (bi_version() == 40)) ) {
        n_data = false;
        m_data = new bmp_data_t(m__io, this, m__root);
    }
}

rage_of_mages_1_bmp_t::~rage_of_mages_1_bmp_t() {
    if (!n_data) {
        delete m_data;
    }
}

rage_of_mages_1_bmp_t::bmp_data_t::bmp_data_t(kaitai::kstream* p__io, rage_of_mages_1_bmp_t* p__parent, rage_of_mages_1_bmp_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_pixels_data = false;
    _read();
}

void rage_of_mages_1_bmp_t::bmp_data_t::_read() {
    m_width = m__io->read_u4le();
    m_height = m__io->read_u4le();
    m_bi_planes_unused = m__io->read_u2le();
    m_bi_bitcount = m__io->read_u2le();
    m_bi_compression_unused = m__io->read_u4le();
    m_bi_sizeimage_unused = m__io->read_u4le();
    m_bi_xpelspermeter_unused = m__io->read_u4le();
    m_bi_ypelspermeter_unused = m__io->read_u4le();
    m_bi_clrused_unused = m__io->read_u4le();
    m_bi_clrimportant_unused = m__io->read_u4le();
    n_palette = true;
    if (bi_bitcount() == 8) {
        n_palette = false;
        int l_palette = 256;
        m_palette = new std::vector<uint32_t>();
        m_palette->reserve(l_palette);
        for (int i = 0; i < l_palette; i++) {
            m_palette->push_back(m__io->read_u4le());
        }
    }
}

rage_of_mages_1_bmp_t::bmp_data_t::~bmp_data_t() {
    if (!n_palette) {
        delete m_palette;
    }
    if (f_pixels_data) {
    }
}

std::string rage_of_mages_1_bmp_t::bmp_data_t::pixels_data() {
    if (f_pixels_data)
        return m_pixels_data;
    kaitai::kstream *io = _root()->_io();
    std::streampos _pos = io->pos();
    io->seek(_root()->bfh_pixeldata());
    m_pixels_data = io->read_bytes((((width() * height()) * bi_bitcount()) / 8));
    io->seek(_pos);
    f_pixels_data = true;
    return m_pixels_data;
}
