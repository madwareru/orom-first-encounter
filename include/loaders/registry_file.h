#ifndef REGISTRY_FILE_H
#define REGISTRY_FILE_H

#include <fstream>
#include <kaitaistruct.h>
#include <loaders/ksy/rage_of_mages_1_reg.h>
#include <tuple>
#include <cstdint>
#include <type_traits>
#include <array>

template<typename T>
struct FieldDefinition {
    typedef T type;
    const char* reg_name;
};

using IntField = FieldDefinition<int32_t>;
using DoubleField = FieldDefinition<double>;
using StringField = FieldDefinition<std::string>;

using i32_array = std::vector<int32_t>;
using IntArrayField = FieldDefinition<i32_array>;

template<typename T>
struct MemberDefinition {
    size_t obj_offset;
    FieldDefinition<T> field_def;
};

struct RegistryFile
{
    template<typename T>
    struct RecordEntry {
        bool exists;
        T content;
    };

    template<typename... Args>
    struct some_struct {
        std::array<std::string, sizeof...(Args)> record_names;
        std::array<bool, sizeof...(Args)> record_existing;
        std::tuple<typename Args::type...> records;
        bool exists(const std::string& rec_name) {
            for(size_t i = 0; i < record_names.size(); ++i) {
                if(record_names.at(i).compare(rec_name) == 0) {
                    return record_existing.at(i);
                }
            }
            return false;
        }
        template<typename T>
        T get(const std::string& rec_name) {
            for(size_t i = 0; i < record_names.size(); ++i) {
                if(record_names.at(i).compare(rec_name) == 0) {
                    auto v = std::get<i>(records);
                    using TT = std::decay_t<decltype(v)>;
                    if constexpr(std::is_same_v<TT, T>) {
                        return v;
                    } else {
                        throw std::runtime_error("wrong type :(");
                    }
                }
            }
            throw std::runtime_error("no such entry");
        }
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

    template<typename TBuffer, typename T>
    bool read_into_buffer(TBuffer* buffer, const char* prefix, MemberDefinition<T> arg) {
        if constexpr(std::is_standard_layout_v<TBuffer>) {
            auto v = read(prefix, arg.field_def);
            if(!v.exists) {
                return false;
            }
            *((T*)(((uint8_t*)buffer) + arg.obj_offset)) = v.content;
            return true;
        } else {
            return false;
        }
    }

    template<typename TBuffer, typename T, typename... Args>
    bool read_into_buffer(TBuffer* buffer, const char* prefix, MemberDefinition<T> arg, MemberDefinition<Args>... args) {
        if constexpr(std::is_standard_layout_v<TBuffer>) {
            return read_into_buffer(buffer, prefix, arg) && read_into_buffer(buffer, prefix, args...);
        } else {
            return false;
        }
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
        if(!success) {
            auto [int_fallback_cuccess, i_entry] = get_int(buffer);
            if(int_fallback_cuccess) {
                return RecordEntry<i32_array>{true, i32_array{i_entry}};
            }
        }
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

template<typename T>
MemberDefinition<T> make_member_def(size_t offset, const char* reg_name) {
    return MemberDefinition{offset, FieldDefinition<T>{reg_name}};
}

#endif // REGISTRY_FILE_H
