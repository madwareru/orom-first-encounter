#ifndef REGISTRY_FILE_H
#define REGISTRY_FILE_H

#include <fstream>
#include <kaitaistruct.h>
#include <loaders/ksy/rage_of_mages_1_reg.h>
#include <tuple>

struct RegistryFile
{
    RegistryFile(const char* file_name);
    RegistryFile(const std::string& byte_buffer);

    RegistryFile(const RegistryFile&) = delete;
    RegistryFile& operator=(const RegistryFile&) = delete;
    RegistryFile(RegistryFile&&) = delete;
    RegistryFile& operator=(RegistryFile&&) = delete;

    std::tuple<bool, int> get_int(const char* path) const;
    std::tuple<bool, double> get_double(const char* path) const;
    std::tuple<bool, std::string> get_string(const char* path) const;
    std::tuple<bool, std::vector<int32_t>> get_int_array(const char* path) const;

    ~RegistryFile();
private:
    rage_of_mages_1_reg_t::registry_header_t* get_registry_header(const char* path) const;

    std::string byte_buffer_{""};
    std::ifstream* in_file_stream_{nullptr};
    kaitai::kstream* kaitai_stream_{nullptr};
    rage_of_mages_1_reg_t* registry_file_nodes_{nullptr};
};

#endif // REGISTRY_FILE_H
