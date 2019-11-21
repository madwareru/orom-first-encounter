#include "resource_file.h"
#include <iostream>
#include "../macro_shared.h"

ResourceFile::ResourceFile(const char* fileName)
{
    in_file_stream_ = new std::ifstream{fileName, std::ifstream::binary};
    kaitai_stream_ = new kaitai::kstream{in_file_stream_};
    resource_file_nodes_ = new rage_of_mages_1_res_t{kaitai_stream_};
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
                LOG_ERROR("Too long filename occured. Not enough size of a buffer");
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
            LOG("successfully found subdir " << buffer);
            goto subdir_found;
        }
        LOG_ERROR("Subdirectory with a name " << buffer << " not found");
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
        LOG("File resource with a name " << buffer << " found");
        return file_resource;
    }
    LOG_ERROR("File resource with a name " << buffer << " not found");
    return nullptr;
}

// This may throw an exception when resource user have read wasn't exist or didn't contained an actual registy file
std::unique_ptr<RegistryFile> ResourceFile::read_registry_res_unique(const char* path){
    auto reg_resource = get_resource(path);
    if(reg_resource == nullptr) {
        throw std::exception("Resource doesn't exist");
    }
    return std::make_unique<RegistryFile>(reg_resource->bytes());
}

// This may throw an exception when resource user have read wasn't exist or didn't contained an actual registy file
std::shared_ptr<RegistryFile> ResourceFile::read_registry_res_shared(const char* path){
    auto reg_resource = get_resource(path);
    if(reg_resource == nullptr) {
        throw std::exception("Resource doesn't exist");
    }
    return std::make_shared<RegistryFile>(reg_resource->bytes());
}

std::tuple<bool, RegistryFile*> ResourceFile::read_registry_res(const char* path) {
    auto reg_resource = get_resource(path);
    if(reg_resource == nullptr) {
        return std::make_tuple(false, nullptr);
    }
    RegistryFile* result = nullptr;
    auto success = true;
    try {
        result = new RegistryFile{reg_resource->bytes()};
    } catch (const std::exception& ex) {
        LOG_ERROR(ex.what());
        success = false;
        if(result != nullptr) {
            delete result;
            result = nullptr;
        }
    }
    return std::make_tuple(success, result);
}

ResourceFile::~ResourceFile() {
    if(resource_file_nodes_ != nullptr) delete resource_file_nodes_;
    if(kaitai_stream_ != nullptr) delete kaitai_stream_;
    if(in_file_stream_ != nullptr) delete in_file_stream_;
}


