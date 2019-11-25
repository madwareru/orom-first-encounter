#include <loaders/resource_file.h>
#include <iostream>
#include <util/macro_shared.h>
#include <loaders/ksy/rage_of_mages_1_bmp.h>

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
        return file_resource;
    }
    LOG_ERROR("File resource with a name " << buffer << " not found");
    return nullptr;
}

std::tuple<bool, std::unique_ptr<RegistryFile>> ResourceFile::read_registry_res_unique(const char* path){
    try {
        auto reg_resource = get_resource(path);
        if(reg_resource == nullptr) {
            LOG_ERROR("Resource not found");
            return std::make_tuple(false, std::unique_ptr<RegistryFile>{nullptr});
        }
        try {
            auto registry_file = new RegistryFile{reg_resource->bytes()};
            return std::make_tuple(true, std::unique_ptr<RegistryFile>{registry_file});
        } catch (const std::exception& ex) {
            LOG_ERROR(ex.what());
            return std::make_tuple(false, std::unique_ptr<RegistryFile>{nullptr});
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(ex.what());
        return std::make_tuple(false, std::unique_ptr<RegistryFile>{nullptr});
    }
}

std::tuple<bool, std::shared_ptr<RegistryFile>> ResourceFile::read_registry_res_shared(const char* path){
    try {
        auto reg_resource = get_resource(path);
        if(reg_resource == nullptr) {
            LOG_ERROR("Resource not found");
            return std::make_tuple(false, std::shared_ptr<RegistryFile>{nullptr});
        }
        try {
            auto registry_file = new RegistryFile{reg_resource->bytes()};
            return std::make_tuple(true, std::shared_ptr<RegistryFile>{registry_file});
        } catch (const std::exception& ex) {
            LOG_ERROR(ex.what());
            return std::make_tuple(false, std::shared_ptr<RegistryFile>{nullptr});
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(ex.what());
        return std::make_tuple(false, std::shared_ptr<RegistryFile>{nullptr});
    }
}

std::tuple<bool, std::shared_ptr<SOASpriteRGB>> ResourceFile::read_bmp_shared(const char* path) {
    try {
        auto bmp_resource = get_resource(path);
        if(bmp_resource == nullptr) {
            LOG_ERROR("Resource not found");
            return std::make_tuple(false, std::make_shared<SOASpriteRGB>(1,1));
        }
        auto bytes = bmp_resource->bytes();
        kaitai::kstream ks{bytes};
        rage_of_mages_1_bmp_t bmp_file{&ks};

        if(bmp_file.bi_version() != 40) {
            LOG_ERROR("this version of bmp not supported");
            return std::make_tuple(false, std::make_shared<SOASpriteRGB>(1,1));
        }

        if(bmp_file.data() == nullptr) {
            LOG_ERROR("data is null");
            return std::make_tuple(false, std::make_shared<SOASpriteRGB>(1,1));
        }

        auto result = std::make_shared<SOASpriteRGB>(bmp_file.data()->width(), bmp_file.data()->height());
        result->mutate([&](auto w, auto h, auto rbuf, auto gbuf, auto bbuf) {
            size_t d_offset = h * w - w;
            auto bit_count = bmp_file.data()->bi_bitcount();
            size_t slide_back = w * 2 * bit_count / 8;
            size_t s_offset = 0;
            for(size_t j = h; j; --j) {
                switch (bmp_file.data()->bi_bitcount()) {
                    case 8: {
                        auto palette = bmp_file.data()->palette();
                        for(size_t i = w; i ; --i) {
                            auto idx = static_cast<uint8_t>(bmp_file.data()->pixels_data().at(s_offset++));
                            auto clr = palette->at(idx);

                            uint8_t b = clr & 0xFF; clr = clr / 0x100;
                            uint8_t g = clr & 0xFF; clr = clr / 0x100;
                            uint8_t r = clr & 0xFF;

                            if(b <= 127) b *= 2; else b = 255;
                            if(g <= 127) g *= 2; else g = 255;
                            if(r <= 127) r *= 2; else r = 255;

                            bbuf[d_offset] = b;
                            gbuf[d_offset] = g;
                            rbuf[d_offset++] = r;
                        }
                    } break;
                    case 24: {
                        for(size_t i = w; i; --i) {
                            rbuf[d_offset] = static_cast<uint8_t>(bmp_file.data()->pixels_data().at(s_offset++));
                            gbuf[d_offset] = static_cast<uint8_t>(bmp_file.data()->pixels_data().at(s_offset++));
                            bbuf[d_offset++] = static_cast<uint8_t>(bmp_file.data()->pixels_data().at(s_offset++));
                        }
                    } break;
                    case 32: {
                        for(size_t i = w; i ; --i) {
                            rbuf[d_offset] = static_cast<uint8_t>(bmp_file.data()->pixels_data().at(s_offset++));
                            gbuf[d_offset] = static_cast<uint8_t>(bmp_file.data()->pixels_data().at(s_offset++));
                            bbuf[d_offset++] = static_cast<uint8_t>(bmp_file.data()->pixels_data().at(s_offset++));
                            ++s_offset;
                        }
                    } break;
                    default:
                        LOG_ERROR("unsupported bitcount detected");
                        return std::make_tuple(false, std::make_shared<SOASpriteRGB>(1,1));
                        break;
                }
                d_offset -= slide_back;
            }
        });
        return std::make_tuple(true, result);
    } catch (const std::exception& ex) {
        LOG_ERROR(ex.what());
        return std::make_tuple(false, std::make_shared<SOASpriteRGB>(1,1));
    }
}

promise_hpp::promise<std::shared_ptr<RegistryFile>> ResourceFile::borrow_registry_resource(const char *path) {
    return promise_hpp::make_promise<std::shared_ptr<RegistryFile>>(
        [&](auto&& resolver, auto&& rejector)
        {
            auto reg_resource = get_resource(path);
            if(reg_resource == nullptr) {
                rejector(std::runtime_error("Resource doesn't exist"));
            }
            try {
                auto result = std::make_shared<RegistryFile>(reg_resource->bytes());
                resolver(result);
            } catch (const std::exception& ex) {
                LOG_ERROR(ex.what());
                rejector(ex);
            }
        });
}


ResourceFile::~ResourceFile() {
    if(resource_file_nodes_ != nullptr) delete resource_file_nodes_;
    if(kaitai_stream_ != nullptr) delete kaitai_stream_;
    if(in_file_stream_ != nullptr) delete in_file_stream_;
}


