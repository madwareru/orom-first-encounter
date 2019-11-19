#ifndef RAGE_OF_MAGES_1_RES_H_
#define RAGE_OF_MAGES_1_RES_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include <kaitaistruct.h>

#include <stdint.h>
#include <vector>

class rage_of_mages_1_res_t : public kaitai::kstruct {

public:
    class directory_resource_t;
    class file_resource_t;
    class resource_header_t;
    class root_resource_header_t_t;
    class resource_header_list_t;

    enum resource_type_e_t {
        RESOURCE_TYPE_E_FILE = 0,
        RESOURCE_TYPE_E_DIRECTORY = 1
    };

    rage_of_mages_1_res_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, rage_of_mages_1_res_t* p__root = 0);

private:
    void _read();

public:
    ~rage_of_mages_1_res_t();

    class directory_resource_t : public kaitai::kstruct {

    public:

        directory_resource_t(kaitai::kstream* p__io, rage_of_mages_1_res_t::resource_header_t* p__parent = 0, rage_of_mages_1_res_t* p__root = 0);

    private:
        void _read();

    public:
        ~directory_resource_t();

    private:
        bool f_nodes;
        resource_header_list_t* m_nodes;

    public:
        resource_header_list_t* nodes();

    private:
        std::string m_directory_name;
        rage_of_mages_1_res_t* m__root;
        rage_of_mages_1_res_t::resource_header_t* m__parent;
        std::string m__raw_nodes;
        kaitai::kstream* m__io__raw_nodes;

    public:
        std::string directory_name() const { return m_directory_name; }
        rage_of_mages_1_res_t* _root() const { return m__root; }
        rage_of_mages_1_res_t::resource_header_t* _parent() const { return m__parent; }
        std::string _raw_nodes() const { return m__raw_nodes; }
        kaitai::kstream* _io__raw_nodes() const { return m__io__raw_nodes; }
    };

    class file_resource_t : public kaitai::kstruct {

    public:

        file_resource_t(kaitai::kstream* p__io, rage_of_mages_1_res_t::resource_header_t* p__parent = 0, rage_of_mages_1_res_t* p__root = 0);

    private:
        void _read();

    public:
        ~file_resource_t();

    private:
        bool f_bytes;
        std::string m_bytes;

    public:
        std::string bytes();

    private:
        std::string m_file_name;
        rage_of_mages_1_res_t* m__root;
        rage_of_mages_1_res_t::resource_header_t* m__parent;

    public:
        std::string file_name() const { return m_file_name; }
        rage_of_mages_1_res_t* _root() const { return m__root; }
        rage_of_mages_1_res_t::resource_header_t* _parent() const { return m__parent; }
    };

    class resource_header_t : public kaitai::kstruct {

    public:

        resource_header_t(kaitai::kstream* p__io, rage_of_mages_1_res_t::resource_header_list_t* p__parent = 0, rage_of_mages_1_res_t* p__root = 0);

    private:
        void _read();

    public:
        ~resource_header_t();

    private:
        uint32_t m_junk;
        uint32_t m_root_offset;
        uint32_t m_root_size;
        resource_type_e_t m_resource_type;
        kaitai::kstruct* m_resource;
        bool n_resource;

    public:
        bool _is_null_resource() { resource(); return n_resource; };

    private:
        rage_of_mages_1_res_t* m__root;
        rage_of_mages_1_res_t::resource_header_list_t* m__parent;

    public:
        uint32_t junk() const { return m_junk; }
        uint32_t root_offset() const { return m_root_offset; }
        uint32_t root_size() const { return m_root_size; }
        resource_type_e_t resource_type() const { return m_resource_type; }
        kaitai::kstruct* resource() const { return m_resource; }
        rage_of_mages_1_res_t* _root() const { return m__root; }
        rage_of_mages_1_res_t::resource_header_list_t* _parent() const { return m__parent; }
    };

    class root_resource_header_t_t : public kaitai::kstruct {

    public:

        root_resource_header_t_t(kaitai::kstream* p__io, rage_of_mages_1_res_t* p__parent = 0, rage_of_mages_1_res_t* p__root = 0);

    private:
        void _read();

    public:
        ~root_resource_header_t_t();

    private:
        uint32_t m_root_offset;
        uint32_t m_root_size;
        uint32_t m_resource_flags;
        uint32_t m_fat_offset;
        uint32_t m_fat_size;
        rage_of_mages_1_res_t* m__root;
        rage_of_mages_1_res_t* m__parent;

    public:
        uint32_t root_offset() const { return m_root_offset; }
        uint32_t root_size() const { return m_root_size; }

        /**
         * not used???
         */
        uint32_t resource_flags() const { return m_resource_flags; }
        uint32_t fat_offset() const { return m_fat_offset; }

        /**
         * not used???
         */
        uint32_t fat_size() const { return m_fat_size; }
        rage_of_mages_1_res_t* _root() const { return m__root; }
        rage_of_mages_1_res_t* _parent() const { return m__parent; }
    };

    class resource_header_list_t : public kaitai::kstruct {

    public:

        resource_header_list_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, rage_of_mages_1_res_t* p__root = 0);

    private:
        void _read();

    public:
        ~resource_header_list_t();

    private:
        std::vector<resource_header_t*>* m_header;
        rage_of_mages_1_res_t* m__root;
        kaitai::kstruct* m__parent;
        std::vector<std::string>* m__raw_header;
        std::vector<kaitai::kstream*>* m__io__raw_header;

    public:
        std::vector<resource_header_t*>* header() const { return m_header; }
        rage_of_mages_1_res_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
        std::vector<std::string>* _raw_header() const { return m__raw_header; }
        std::vector<kaitai::kstream*>* _io__raw_header() const { return m__io__raw_header; }
    };

private:
    bool f_nodes;
    resource_header_list_t* m_nodes;

public:
    resource_header_list_t* nodes();

private:
    std::string m_signature;
    root_resource_header_t_t* m_resource_header;
    rage_of_mages_1_res_t* m__root;
    kaitai::kstruct* m__parent;
    std::string m__raw_nodes;
    kaitai::kstream* m__io__raw_nodes;

public:
    std::string signature() const { return m_signature; }
    root_resource_header_t_t* resource_header() const { return m_resource_header; }
    rage_of_mages_1_res_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
    std::string _raw_nodes() const { return m__raw_nodes; }
    kaitai::kstream* _io__raw_nodes() const { return m__io__raw_nodes; }
};

#endif  // RAGE_OF_MAGES_1_RES_H_
