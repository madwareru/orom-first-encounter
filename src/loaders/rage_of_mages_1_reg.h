#ifndef RAGE_OF_MAGES_1_REG_H_
#define RAGE_OF_MAGES_1_REG_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include <kaitaistruct.h>

#include <stdint.h>
#include <vector>

class rage_of_mages_1_reg_t : public kaitai::kstruct {

public:
    class registry_header_list_t;
    class directory_entry_t;
    class byte_entry_t;
    class string_entry_t;
    class registry_header_t;
    class int_array_entry_t;
    class int_entry_t;
    class float_entry_t;
    class root_registry_header_t_t;

    enum registry_type_e_t {
        REGISTRY_TYPE_E_STRING = 0,
        REGISTRY_TYPE_E_DIRECTORY = 1,
        REGISTRY_TYPE_E_INT = 2,
        REGISTRY_TYPE_E_FLOAT = 4,
        REGISTRY_TYPE_E_INT_ARRAY = 6
    };

    rage_of_mages_1_reg_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, rage_of_mages_1_reg_t* p__root = 0);

private:
    void _read();

public:
    ~rage_of_mages_1_reg_t();

    class registry_header_list_t : public kaitai::kstruct {

    public:

        registry_header_list_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, rage_of_mages_1_reg_t* p__root = 0);

    private:
        void _read();

    public:
        ~registry_header_list_t();

    private:
        std::vector<registry_header_t*>* m_header;
        rage_of_mages_1_reg_t* m__root;
        kaitai::kstruct* m__parent;
        std::vector<std::string>* m__raw_header;
        std::vector<kaitai::kstream*>* m__io__raw_header;

    public:
        std::vector<registry_header_t*>* header() const { return m_header; }
        rage_of_mages_1_reg_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
        std::vector<std::string>* _raw_header() const { return m__raw_header; }
        std::vector<kaitai::kstream*>* _io__raw_header() const { return m__io__raw_header; }
    };

    class directory_entry_t : public kaitai::kstruct {

    public:

        directory_entry_t(kaitai::kstream* p__io, rage_of_mages_1_reg_t::registry_header_t* p__parent = 0, rage_of_mages_1_reg_t* p__root = 0);

    private:
        void _read();

    public:
        ~directory_entry_t();

    private:
        bool f_value;
        registry_header_list_t* m_value;

    public:
        registry_header_list_t* value();

    private:
        uint32_t m_e_offset;
        uint32_t m_e_count;
        rage_of_mages_1_reg_t* m__root;
        rage_of_mages_1_reg_t::registry_header_t* m__parent;
        std::string m__raw_value;
        kaitai::kstream* m__io__raw_value;

    public:
        uint32_t e_offset() const { return m_e_offset; }
        uint32_t e_count() const { return m_e_count; }
        rage_of_mages_1_reg_t* _root() const { return m__root; }
        rage_of_mages_1_reg_t::registry_header_t* _parent() const { return m__parent; }
        std::string _raw_value() const { return m__raw_value; }
        kaitai::kstream* _io__raw_value() const { return m__io__raw_value; }
    };

    class byte_entry_t : public kaitai::kstruct {

    public:

        byte_entry_t(kaitai::kstream* p__io, rage_of_mages_1_reg_t::registry_header_t* p__parent = 0, rage_of_mages_1_reg_t* p__root = 0);

    private:
        void _read();

    public:
        ~byte_entry_t();

    private:
        uint8_t m_value;
        rage_of_mages_1_reg_t* m__root;
        rage_of_mages_1_reg_t::registry_header_t* m__parent;

    public:
        uint8_t value() const { return m_value; }
        rage_of_mages_1_reg_t* _root() const { return m__root; }
        rage_of_mages_1_reg_t::registry_header_t* _parent() const { return m__parent; }
    };

    class string_entry_t : public kaitai::kstruct {

    public:

        string_entry_t(kaitai::kstream* p__io, rage_of_mages_1_reg_t::registry_header_t* p__parent = 0, rage_of_mages_1_reg_t* p__root = 0);

    private:
        void _read();

    public:
        ~string_entry_t();

    private:
        bool f_value;
        std::string m_value;

    public:
        std::string value();

    private:
        uint32_t m_e_offset;
        uint32_t m_e_count;
        rage_of_mages_1_reg_t* m__root;
        rage_of_mages_1_reg_t::registry_header_t* m__parent;

    public:
        uint32_t e_offset() const { return m_e_offset; }
        uint32_t e_count() const { return m_e_count; }
        rage_of_mages_1_reg_t* _root() const { return m__root; }
        rage_of_mages_1_reg_t::registry_header_t* _parent() const { return m__parent; }
    };

    class registry_header_t : public kaitai::kstruct {

    public:

        registry_header_t(kaitai::kstream* p__io, rage_of_mages_1_reg_t::registry_header_list_t* p__parent = 0, rage_of_mages_1_reg_t* p__root = 0);

    private:
        void _read();

    public:
        ~registry_header_t();

    private:
        bool f_e_type;
        registry_type_e_t m_e_type;

    public:
        registry_type_e_t e_type();

    private:
        uint32_t m_junk;
        kaitai::kstruct* m_value;
        uint32_t m_typ;
        std::string m_name;
        rage_of_mages_1_reg_t* m__root;
        rage_of_mages_1_reg_t::registry_header_list_t* m__parent;
        std::string m__raw_value;
        kaitai::kstream* m__io__raw_value;

    public:
        uint32_t junk() const { return m_junk; }
        kaitai::kstruct* value() const { return m_value; }
        uint32_t typ() const { return m_typ; }
        std::string name() const { return m_name; }
        rage_of_mages_1_reg_t* _root() const { return m__root; }
        rage_of_mages_1_reg_t::registry_header_list_t* _parent() const { return m__parent; }
        std::string _raw_value() const { return m__raw_value; }
        kaitai::kstream* _io__raw_value() const { return m__io__raw_value; }
    };

    class int_array_entry_t : public kaitai::kstruct {

    public:

        int_array_entry_t(kaitai::kstream* p__io, rage_of_mages_1_reg_t::registry_header_t* p__parent = 0, rage_of_mages_1_reg_t* p__root = 0);

    private:
        void _read();

    public:
        ~int_array_entry_t();

    private:
        bool f_value;
        std::vector<int32_t>* m_value;

    public:
        std::vector<int32_t>* value();

    private:
        uint32_t m_e_offset;
        uint32_t m_e_size;
        rage_of_mages_1_reg_t* m__root;
        rage_of_mages_1_reg_t::registry_header_t* m__parent;

    public:
        uint32_t e_offset() const { return m_e_offset; }
        uint32_t e_size() const { return m_e_size; }
        rage_of_mages_1_reg_t* _root() const { return m__root; }
        rage_of_mages_1_reg_t::registry_header_t* _parent() const { return m__parent; }
    };

    class int_entry_t : public kaitai::kstruct {

    public:

        int_entry_t(kaitai::kstream* p__io, rage_of_mages_1_reg_t::registry_header_t* p__parent = 0, rage_of_mages_1_reg_t* p__root = 0);

    private:
        void _read();

    public:
        ~int_entry_t();

    private:
        int32_t m_value;
        rage_of_mages_1_reg_t* m__root;
        rage_of_mages_1_reg_t::registry_header_t* m__parent;

    public:
        int32_t value() const { return m_value; }
        rage_of_mages_1_reg_t* _root() const { return m__root; }
        rage_of_mages_1_reg_t::registry_header_t* _parent() const { return m__parent; }
    };

    class float_entry_t : public kaitai::kstruct {

    public:

        float_entry_t(kaitai::kstream* p__io, rage_of_mages_1_reg_t::registry_header_t* p__parent = 0, rage_of_mages_1_reg_t* p__root = 0);

    private:
        void _read();

    public:
        ~float_entry_t();

    private:
        double m_value;
        rage_of_mages_1_reg_t* m__root;
        rage_of_mages_1_reg_t::registry_header_t* m__parent;

    public:
        double value() const { return m_value; }
        rage_of_mages_1_reg_t* _root() const { return m__root; }
        rage_of_mages_1_reg_t::registry_header_t* _parent() const { return m__parent; }
    };

    class root_registry_header_t_t : public kaitai::kstruct {

    public:

        root_registry_header_t_t(kaitai::kstream* p__io, rage_of_mages_1_reg_t* p__parent = 0, rage_of_mages_1_reg_t* p__root = 0);

    private:
        void _read();

    public:
        ~root_registry_header_t_t();

    private:
        bool f_data_origin;
        int32_t m_data_origin;

    public:
        int32_t data_origin();

    private:
        uint32_t m_root_offset;
        uint32_t m_root_size;
        uint32_t m_registry_flags;
        uint32_t m_registry_eat_size;
        uint32_t m_junk;
        rage_of_mages_1_reg_t* m__root;
        rage_of_mages_1_reg_t* m__parent;

    public:
        uint32_t root_offset() const { return m_root_offset; }
        uint32_t root_size() const { return m_root_size; }

        /**
         * not used???
         */
        uint32_t registry_flags() const { return m_registry_flags; }
        uint32_t registry_eat_size() const { return m_registry_eat_size; }

        /**
         * not used???
         */
        uint32_t junk() const { return m_junk; }
        rage_of_mages_1_reg_t* _root() const { return m__root; }
        rage_of_mages_1_reg_t* _parent() const { return m__parent; }
    };

private:
    bool f_nodes;
    registry_header_list_t* m_nodes;

public:
    registry_header_list_t* nodes();

private:
    std::string m_signature;
    root_registry_header_t_t* m_registry_header;
    rage_of_mages_1_reg_t* m__root;
    kaitai::kstruct* m__parent;
    std::string m__raw_nodes;
    kaitai::kstream* m__io__raw_nodes;

public:
    std::string signature() const { return m_signature; }
    root_registry_header_t_t* registry_header() const { return m_registry_header; }
    rage_of_mages_1_reg_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
    std::string _raw_nodes() const { return m__raw_nodes; }
    kaitai::kstream* _io__raw_nodes() const { return m__io__raw_nodes; }
};

#endif  // RAGE_OF_MAGES_1_REG_H_
