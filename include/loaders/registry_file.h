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

using IntField = FieldDefinition<int32_t>;
using DoubleField = FieldDefinition<double>;
using StringField = FieldDefinition<std::string>;

using i32_array = std::vector<int32_t>;
using IntArrayField = FieldDefinition<i32_array>;

struct RegistryFile
{
    template<typename T>
    struct RecordEntry {
        bool exists;
        T content;
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
    auto read_record(const char* prefix, FieldDefinition<Args>... args){
        return std::make_tuple(read(prefix, args)...);
    }

    ~RegistryFile();
private:
    template<typename T>
    RecordEntry<T> read(const char* prefix, FieldDefinition<T> field);

    template<>
    RecordEntry<int32_t> read(const char* prefix, IntField field) {
        char buffer[256];
        sprintf(buffer, "%s%s", prefix, field.reg_name);
        auto [success, i_entry] = get_int(buffer);
        return RecordEntry<int32_t>{ success, i_entry};
    }

    template<>
    RecordEntry<double> read(const char* prefix, DoubleField field) {
        char buffer[256];
        sprintf(buffer, "%s%s", prefix, field.reg_name);
        auto [success, d_entry] = get_double(buffer);
        return RecordEntry<double>{ success, d_entry};
    }

    template<>
    RecordEntry<i32_array> read(const char* prefix, IntArrayField field) {
        char buffer[256];
        sprintf(buffer, "%s%s", prefix, field.reg_name);
        auto [success, ia_entry] = get_int_array(buffer);
        return RecordEntry<i32_array>{ success, ia_entry};
    }

    template<>
    RecordEntry<std::string> read(const char* prefix, StringField field) {
        char buffer[256];
        sprintf(buffer, "%s%s", prefix, field.reg_name);
        auto [success, s_entry] = get_string(buffer);
        return RecordEntry<std::string>{ success, s_entry};
    }

    rage_of_mages_1_reg_t::registry_header_t* get_registry_header(const char* path) const;

    std::string byte_buffer_{""};
    std::ifstream* in_file_stream_{nullptr};
    kaitai::kstream* kaitai_stream_{nullptr};
    rage_of_mages_1_reg_t* registry_file_nodes_{nullptr};
};

#endif // REGISTRY_FILE_H
