// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include <loaders/ksy/rage_of_mages_1_txt_866.h>

rage_of_mages_1_txt_866_t::rage_of_mages_1_txt_866_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, rage_of_mages_1_txt_866_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    _read();
}

void rage_of_mages_1_txt_866_t::_read() {
    m_content = kaitai::kstream::bytes_to_str(m__io->read_bytes(_io()->size()), std::string("IBM866"));
}

rage_of_mages_1_txt_866_t::~rage_of_mages_1_txt_866_t() {
}
