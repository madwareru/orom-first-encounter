#ifndef RAGE_OF_MAGES_1_TXT_866_H_
#define RAGE_OF_MAGES_1_TXT_866_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include <kaitaistruct.h>

#include <stdint.h>

class rage_of_mages_1_txt_866_t : public kaitai::kstruct {

public:

    rage_of_mages_1_txt_866_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, rage_of_mages_1_txt_866_t* p__root = 0);

private:
    void _read();

public:
    ~rage_of_mages_1_txt_866_t();

private:
    std::string m_content;
    rage_of_mages_1_txt_866_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::string content() const { return m_content; }
    rage_of_mages_1_txt_866_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // RAGE_OF_MAGES_1_TXT_866_H_
