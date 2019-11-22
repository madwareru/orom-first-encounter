#ifndef RAGE_OF_MAGES_1_BMP_H_
#define RAGE_OF_MAGES_1_BMP_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include <kaitaistruct.h>

#include <stdint.h>
#include <vector>

/**
 * This format is just a subtype of a typical bmp file format used in ROM
 */

class rage_of_mages_1_bmp_t : public kaitai::kstruct {

public:
    class bmp_data_t;

    rage_of_mages_1_bmp_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, rage_of_mages_1_bmp_t* p__root = 0);

private:
    void _read();

public:
    ~rage_of_mages_1_bmp_t();

    class bmp_data_t : public kaitai::kstruct {

    public:

        bmp_data_t(kaitai::kstream* p__io, rage_of_mages_1_bmp_t* p__parent = 0, rage_of_mages_1_bmp_t* p__root = 0);

    private:
        void _read();

    public:
        ~bmp_data_t();

    private:
        bool f_pixels_data;
        std::string m_pixels_data;

    public:
        std::string pixels_data();

    private:
        uint32_t m_width;
        uint32_t m_height;
        uint16_t m_bi_planes_unused;
        uint16_t m_bi_bitcount;
        uint32_t m_bi_compression_unused;
        uint32_t m_bi_sizeimage_unused;
        uint32_t m_bi_xpelspermeter_unused;
        uint32_t m_bi_ypelspermeter_unused;
        uint32_t m_bi_clrused_unused;
        uint32_t m_bi_clrimportant_unused;
        std::vector<uint32_t>* m_palette;
        bool n_palette;

    public:
        bool _is_null_palette() { palette(); return n_palette; };

    private:
        rage_of_mages_1_bmp_t* m__root;
        rage_of_mages_1_bmp_t* m__parent;

    public:
        uint32_t width() const { return m_width; }
        uint32_t height() const { return m_height; }
        uint16_t bi_planes_unused() const { return m_bi_planes_unused; }
        uint16_t bi_bitcount() const { return m_bi_bitcount; }
        uint32_t bi_compression_unused() const { return m_bi_compression_unused; }
        uint32_t bi_sizeimage_unused() const { return m_bi_sizeimage_unused; }
        uint32_t bi_xpelspermeter_unused() const { return m_bi_xpelspermeter_unused; }
        uint32_t bi_ypelspermeter_unused() const { return m_bi_ypelspermeter_unused; }
        uint32_t bi_clrused_unused() const { return m_bi_clrused_unused; }
        uint32_t bi_clrimportant_unused() const { return m_bi_clrimportant_unused; }
        std::vector<uint32_t>* palette() const { return m_palette; }
        rage_of_mages_1_bmp_t* _root() const { return m__root; }
        rage_of_mages_1_bmp_t* _parent() const { return m__parent; }
    };

private:
    std::string m_magic;
    uint32_t m_unused0;
    uint32_t m_unused1;
    uint32_t m_bfh_pixeldata;
    uint32_t m_bi_version;
    bmp_data_t* m_data;
    bool n_data;

public:
    bool _is_null_data() { data(); return n_data; };

private:
    rage_of_mages_1_bmp_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::string magic() const { return m_magic; }
    uint32_t unused0() const { return m_unused0; }
    uint32_t unused1() const { return m_unused1; }
    uint32_t bfh_pixeldata() const { return m_bfh_pixeldata; }
    uint32_t bi_version() const { return m_bi_version; }
    bmp_data_t* data() const { return m_data; }
    rage_of_mages_1_bmp_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // RAGE_OF_MAGES_1_BMP_H_
