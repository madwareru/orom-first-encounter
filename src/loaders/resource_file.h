#ifndef RESOURCE_FILE_H
#define RESOURCE_FILE_H

#include <fstream>
#include <cstdarg>
#include <kaitaistruct.h>
#include "rage_of_mages_1_res.h"

struct ResourceFile
{
    ResourceFile(std::string fileName);
    ResourceFile(const char* fileName);

    ResourceFile(const ResourceFile&) = delete;
    ResourceFile& operator=(const ResourceFile&) = delete;
    ResourceFile(ResourceFile&&) = delete;
    ResourceFile& operator=(ResourceFile&&) = delete;

    rage_of_mages_1_res_t::file_resource_t* get_resource(const char* path);

    ~ResourceFile();
private:
    std::ifstream* in_file_stream_;
    kaitai::kstream* kaitai_stream_;
    rage_of_mages_1_res_t* resource_file_nodes_;
};

#endif // RESOURCE_FILE_H
