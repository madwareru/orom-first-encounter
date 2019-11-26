#ifndef REGISTRY_FILE_H
#define REGISTRY_FILE_H

#include <fstream>
#include <kaitaistruct.h>
#include <loaders/ksy/rage_of_mages_1_reg.h>
#include <tuple>
#include <cstdint>

template<typename T>
struct FieldDefinition {
    const char* reg_name;
};

using i32       = int32_t;
using stringval = std::string;
using f64       = double;
using i32_array = std::vector<int32_t>;

using IntField = FieldDefinition<i32>;
using DoubleField = FieldDefinition<f64>;
using StringField = FieldDefinition<stringval>;
using IntArrayField = FieldDefinition<i32_array>;

struct RegistryFile
{
    template<typename... Args>
    struct Record{
        size_t field_count;
        char const* * field_names;
        rage_of_mages_1_reg_t::registry_type_e_t* field_types;
        std::tuple<Args...> values;

        Record(
            size_t fieldCount,
            char const* * fieldNames,
            rage_of_mages_1_reg_t::registry_type_e_t* fieldTypes,
            std::tuple<Args...>&& valuess
        ) :
        field_count{fieldCount},
        field_names{fieldNames},
        field_types{fieldTypes},
        values{valuess}{}
    };

    RegistryFile(const char* file_name);
    RegistryFile(const std::string& byte_buffer);

    RegistryFile(const RegistryFile&) = delete;
    RegistryFile& operator=(const RegistryFile&) = delete;
    RegistryFile(RegistryFile&&) = delete;
    RegistryFile& operator=(RegistryFile&&) = delete;

    std::tuple<bool, int32_t> get_int(const char* path) const;
    std::tuple<bool, double> get_double(const char* path) const;
    std::tuple<bool, std::string> get_string(const char* path) const;
    std::tuple<bool, std::vector<int32_t>> get_int_array(const char* path) const;

    template<typename... Args>
    std::tuple<Args...> read_record(const char* shared_prefix, FieldDefinition<Args>... args){
        return std::make_tuple(read(shared_prefix, args)...);
    }

    template<typename... Args>
    struct Record<Args...> read_record2(const char* shared_prefix, FieldDefinition<Args>... args){
        const size_t arg_num = sizeof...(Args);
        const char* f_names[arg_num] = {read_reg_name(args)...};
        rage_of_mages_1_reg_t::registry_type_e_t f_types[arg_num] = {read_reg_type(args)...};
        return Record{
            arg_num,
            f_names,
            f_types,
            std::make_tuple(read(shared_prefix, args)...)
        };
    }

    ~RegistryFile();
private:
    template<typename T>
    const char* read_reg_name(FieldDefinition<T> field) {
        return field.reg_name;
    }

    template<typename T>
    rage_of_mages_1_reg_t::registry_type_e_t read_reg_type(FieldDefinition<T> field);

    template<>
    rage_of_mages_1_reg_t::registry_type_e_t read_reg_type(IntField field) {
        return rage_of_mages_1_reg_t::REGISTRY_TYPE_E_INT;
    }

    template<>
    rage_of_mages_1_reg_t::registry_type_e_t read_reg_type(DoubleField field) {
        return rage_of_mages_1_reg_t::REGISTRY_TYPE_E_FLOAT;
    }

    template<>
    rage_of_mages_1_reg_t::registry_type_e_t read_reg_type(StringField field) {
        return rage_of_mages_1_reg_t::REGISTRY_TYPE_E_STRING;
    }

    template<>
    rage_of_mages_1_reg_t::registry_type_e_t read_reg_type(IntArrayField field) {
        return rage_of_mages_1_reg_t::REGISTRY_TYPE_E_INT_ARRAY;
    }

    template<typename T>
    T read(const char* shared_prefix, FieldDefinition<T> field);

    template<typename T>
    T read(const char* shared_prefix, std::tuple<FieldDefinition<T>> field) {
        field.first;
    }

    template<>
    int32_t read(const char* shared_prefix, IntField field) {
        char buffer[256];
        sprintf(buffer, "%s%s", shared_prefix, field.reg_name);
        auto [success, i_entry] = get_int(buffer);
        if(!success) {
            throw std::runtime_error("unexpected input found by reading int field");
        }
        return i_entry;
    }

    template<>
    double read(const char* shared_prefix, DoubleField field) {
        char buffer[256];
        sprintf(buffer, "%s%s", shared_prefix, field.reg_name);
        auto [success, d_entry] = get_double(buffer);
        if(!success) {
            throw std::runtime_error("unexpected input found by reading int field");
        }
        return d_entry;
    }

    template<>
    std::vector<int32_t> read(const char* shared_prefix, IntArrayField field) {
        char buffer[256];
        sprintf(buffer, "%s%s", shared_prefix, field.reg_name);
        auto [success, ia_entry] = get_int_array(buffer);
        if(!success) {
            throw std::runtime_error("unexpected input found by reading string field");
        }
        return ia_entry;
    }

    template<>
    std::string read(const char* shared_prefix, StringField field) {
        char buffer[256];
        sprintf(buffer, "%s%s", shared_prefix, field.reg_name);
        auto [success, s_entry] = get_string(buffer);
        if(!success) {
            throw std::runtime_error("unexpected input found by reading string field");
        }
        return s_entry;
    }

    rage_of_mages_1_reg_t::registry_header_t* get_registry_header(const char* path) const;

    std::string byte_buffer_{""};
    std::ifstream* in_file_stream_{nullptr};
    kaitai::kstream* kaitai_stream_{nullptr};
    rage_of_mages_1_reg_t* registry_file_nodes_{nullptr};
};

#endif // REGISTRY_FILE_H
