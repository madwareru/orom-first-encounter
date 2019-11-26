#include <loaders/registry_file.h>
#include <iostream>
#include <util/macro_shared.h>

RegistryFile::RegistryFile(const char* file_name)
{
    in_file_stream_ = new std::ifstream{file_name, std::ifstream::binary};
    kaitai_stream_ = new kaitai::kstream{in_file_stream_};
    registry_file_nodes_ = new rage_of_mages_1_reg_t{kaitai_stream_};
}

RegistryFile::RegistryFile(const std::string& byte_buffer) {
    byte_buffer_ = byte_buffer;
    kaitai_stream_ = new kaitai::kstream{byte_buffer_};
    registry_file_nodes_ = new rage_of_mages_1_reg_t{kaitai_stream_};
}

rage_of_mages_1_reg_t::registry_header_t* RegistryFile::get_registry_header(const char *path) const {
    auto header_list = registry_file_nodes_->nodes()->header();
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
            goto search_header;
        }

        buffer_offset = 0;

        for(size_t j = 0; j < header_list->size(); ++j) {
            auto entry = header_list->at(j);
            if(entry->e_type() != rage_of_mages_1_reg_t::REGISTRY_TYPE_E_DIRECTORY) {
                continue;
            }
            auto subdir_entry = dynamic_cast<rage_of_mages_1_reg_t::directory_entry_t*>(entry->value());
            if(entry->name() != buffer) {
                continue;
            }
            LOG("found subdir " << buffer);
            header_list = subdir_entry->value()->header();
            goto subdir_found;
        }
        LOG_ERROR("Subdirectory with a name " << buffer << " not found");
        return nullptr;
        subdir_found: ++i;
    }
    search_header:
    for(size_t j = 0; j < header_list->size(); ++j) {
        auto entry = header_list->at(j);

        if(entry->name() != buffer) {
            continue;
        }
        return entry;
    }
    LOG_ERROR("Registry header with a name " << buffer << " not found");
    return nullptr;
}

std::tuple<bool, int32_t> RegistryFile::get_int(const char *path) const {
    try {
        auto header = get_registry_header(path);
        if(header == nullptr) {
            LOG_ERROR("no such registry entry found");
            return std::make_tuple(false, 0);
        }
        if(header->e_type() != rage_of_mages_1_reg_t::REGISTRY_TYPE_E_INT) {
            LOG_ERROR("registry entry has unexpected type. Make sure you are correct");
            return std::make_tuple(false, 0);
        }
        auto result = std::make_tuple(true, dynamic_cast<rage_of_mages_1_reg_t::int_entry_t*>(header->value())->value());
        return result;
    } catch (const std::exception& ex) {
        LOG_ERROR(ex.what());
        return std::make_tuple(false, 0);
    }
}

std::tuple<bool, double> RegistryFile::get_double(const char *path) const {
    try {
        auto header = get_registry_header(path);
        if(header == nullptr) {
            LOG_ERROR("no such registry entry found");
            return std::make_tuple(false, 0.0);
        }
        if(header->e_type() != rage_of_mages_1_reg_t::REGISTRY_TYPE_E_FLOAT) {
            LOG_ERROR("registry entry has unexpected type. Make sure you are correct");
            return std::make_tuple(false, 0.0);
        }
        auto result = std::make_tuple(true, dynamic_cast<rage_of_mages_1_reg_t::float_entry_t*>(header->value())->value());
        return result;
    } catch (const std::exception& ex) {
        LOG_ERROR(ex.what());
        return std::make_tuple(false, 0.0);
    }
}

std::tuple<bool, std::string> RegistryFile::get_string(const char *path) const {
    try {
        auto header = get_registry_header(path);
        if(header == nullptr) {
            LOG_ERROR("no such registry entry found");
            return std::make_tuple(false, "");
        }
        if(header->e_type() != rage_of_mages_1_reg_t::REGISTRY_TYPE_E_STRING) {
            LOG_ERROR("registry entry has unexpected type. Make sure you are correct");
            return std::make_tuple(false, "0.0");
        }
        auto result = std::make_tuple(true, dynamic_cast<rage_of_mages_1_reg_t::string_entry_t*>(header->value())->value());
        return result;
    } catch (const std::exception& ex) {
        LOG_ERROR(ex.what());
        return std::make_tuple(false, "");
    }
}

std::tuple<bool, std::vector<int32_t>> RegistryFile::get_int_array(const char *path) const {
    try {
        auto header = get_registry_header(path);
        if(header == nullptr) {
            LOG_ERROR("no such registry entry found");
            return std::make_tuple(false, std::vector<int32_t>{});
        }
        if(header->e_type() != rage_of_mages_1_reg_t::REGISTRY_TYPE_E_INT_ARRAY) {
            LOG_ERROR("registry entry has unexpected type. Make sure you are correct");
            return std::make_tuple(false, std::vector<int32_t>{});
        }
        auto result = std::make_tuple(true, *(dynamic_cast<rage_of_mages_1_reg_t::int_array_entry_t*>(header->value())->value()));
        return result;
    } catch (const std::exception& ex) {
        LOG_ERROR(ex.what());
        return std::make_tuple(false, std::vector<int32_t>{});
    }
}

RegistryFile::~RegistryFile() {
    if(registry_file_nodes_ != nullptr) delete registry_file_nodes_;
    if(kaitai_stream_ != nullptr) delete kaitai_stream_;
    if(in_file_stream_ != nullptr) delete in_file_stream_;
}
