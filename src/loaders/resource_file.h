#ifndef RESOURCE_FILE_H
#define RESOURCE_FILE_H

#include <fstream>
#include <kaitaistruct.h>
#include "rage_of_mages_1_res.h"
#include "registry_file.h"
#include <tuple>
#include <memory>

struct ResourceFile
{
    ResourceFile(const char* fileName);

    ResourceFile(const ResourceFile&) = delete;
    ResourceFile& operator=(const ResourceFile&) = delete;
    ResourceFile(ResourceFile&&) = delete;
    ResourceFile& operator=(ResourceFile&&) = delete;

    rage_of_mages_1_res_t::file_resource_t* get_resource(const char* path);

    //
    // This may throw an exception when resource user have read
    // wasn't exist or didn't contained an actual registy file
    //
    std::unique_ptr<RegistryFile> read_registry_res_unique(const char* path);
    //
    // This may throw an exception when resource user have read
    // wasn't exist or didn't contained an actual registy file
    //
    std::shared_ptr<RegistryFile> read_registry_res_shared(const char* path);
    std::tuple<bool, RegistryFile*> read_registry_res(const char* path);

    ~ResourceFile();
private:
    std::ifstream* in_file_stream_{nullptr};
    kaitai::kstream* kaitai_stream_{nullptr};
    rage_of_mages_1_res_t* resource_file_nodes_{nullptr};
};

#endif // RESOURCE_FILE_H
