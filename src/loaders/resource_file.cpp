#include "resource_file.h"
#include <iostream>

#define S1(x) #x
#define S2(x) S1(x)
#define LOCATION __FILE__ " : " S2(__LINE__)

ResourceFile::ResourceFile(std::string fileName)
{
    in_file_stream_ = new std::ifstream(fileName, std::ifstream::binary);
    kaitai_stream_ = new kaitai::kstream(in_file_stream_);
    resource_file_nodes_ = new rage_of_mages_1_res_t(kaitai_stream_);
}

ResourceFile::ResourceFile(const char* fileName)
{
    in_file_stream_ = new std::ifstream(fileName, std::ifstream::binary);
    kaitai_stream_ = new kaitai::kstream(in_file_stream_);
    resource_file_nodes_ = new rage_of_mages_1_res_t(kaitai_stream_);
}

rage_of_mages_1_res_t::file_resource_t* ResourceFile::get_resource(const char* path){
    auto header_list = resource_file_nodes_->nodes()->header();
    char buffer[256];
    size_t buffer_offset = 0;
    bool file_reached = false;
    size_t i = 0;
    for(;;) {
        while(path[i] != '\0' && path[i] != '/') {
            if(buffer_offset >= 256) {
                std::cerr << "Too long filename occured. Not enough size of a buffer(" LOCATION ")" << std::endl;
                return nullptr;
            }
            buffer[buffer_offset++] = path[i++];
        }
        buffer[buffer_offset] = '\0';

        file_reached = (path[i] == '\0');
        if(file_reached) {
            goto search_file;
        }

        buffer_offset = 0;

        for(size_t j = 0; j < header_list->size(); ++j) {
            auto entry = header_list->at(j);
            if(entry->resource_type() == rage_of_mages_1_res_t::RESOURCE_TYPE_E_FILE) {
                continue;
            }
            auto subdir_resource = dynamic_cast<rage_of_mages_1_res_t::directory_resource_t*>(entry->resource());
            if(subdir_resource->directory_name() != buffer) {
                continue;
            }
            header_list = subdir_resource->nodes()->header();
            std::cout << "successfully found subdir " << buffer << std::endl;
            goto subdir_found;
        }
        std::cerr << "Subdirectory with a name " << buffer << " not found (" LOCATION ")" << std::endl;
        return nullptr;
        subdir_found: ++i;
    }
    search_file:
    for(size_t j = 0; j < header_list->size(); ++j) {
        auto entry = header_list->at(j);
        if(entry->resource_type() != rage_of_mages_1_res_t::RESOURCE_TYPE_E_FILE) {
            continue;
        }
        auto file_resource = dynamic_cast<rage_of_mages_1_res_t::file_resource_t*>(entry->resource());
        if(file_resource->file_name() != buffer) {
            continue;
        }
        return file_resource;
    }
    std::cerr << "File resource with a name " << buffer << " not found" << std::endl;
    return nullptr;
}

ResourceFile::~ResourceFile() {
    delete resource_file_nodes_;
    delete kaitai_stream_;
    delete in_file_stream_;
}
