#ifndef RAGE_OF_MAGES_1_16_H_
#define RAGE_OF_MAGES_1_16_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include <kaitaistruct.h>

#include <stdint.h>
#include <vector>

/**
 * This format contains white texture with 16 degrees of transparency
 * Used in the game mainly for fonts
 */

class rage_of_mages_1_16_t : public kaitai::kstruct {

public:
    class sprite_record_t;

    rage_of_mages_1_16_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, rage_of_mages_1_16_t* p__root = 0);

private:
    void _read();

public:
    ~rage_of_mages_1_16_t();

    class sprite_record_t : public kaitai::kstruct {

    public:

        sprite_record_t(kaitai::kstream* p__io, rage_of_mages_1_16_t* p__parent = 0, rage_of_mages_1_16_t* p__root = 0);

    private:
        void _read();

    public:
        ~sprite_record_t();

    private:
        uint32_t m_width;
        uint32_t m_height;
        uint32_t m_data_size;
        std::string m_data;
        rage_of_mages_1_16_t* m__root;
        rage_of_mages_1_16_t* m__parent;

    public:
        uint32_t width() const { return m_width; }
        uint32_t height() const { return m_height; }
        uint32_t data_size() const { return m_data_size; }
        std::string data() const { return m_data; }
        rage_of_mages_1_16_t* _root() const { return m__root; }
        rage_of_mages_1_16_t* _parent() const { return m__parent; }
    };

private:
    bool f_sprite_count_internal;
    uint32_t m_sprite_count_internal;

public:
    uint32_t sprite_count_internal();

private:
    bool f_sprite_count;
    int32_t m_sprite_count;

public:
    int32_t sprite_count();

private:
    std::vector<sprite_record_t*>* m_sprite_records;
    rage_of_mages_1_16_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::vector<sprite_record_t*>* sprite_records() const { return m_sprite_records; }
    rage_of_mages_1_16_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // RAGE_OF_MAGES_1_16_H_
