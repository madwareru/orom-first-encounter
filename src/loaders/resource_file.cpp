#include <loaders/resource_file.h>
#include <iostream>
#include <util/macro_shared.h>
#include <loaders/ksy/rage_of_mages_1_bmp.h>
#include <loaders/ksy/rage_of_mages_1_16a.h>
#include <loaders/ksy/rage_of_mages_1_256.h>
#include <loaders/ksy/rage_of_mages_1_16.h>

#include <graphics/Sprite16.h>
#include <graphics/Sprite16a.h>
#include <graphics/Sprite256.h>
#include <graphics/soaspritergb.h>

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

std::tuple<bool, std::shared_ptr<SOASpriteRGB>> ResourceFile::read_mask_shared(const char* path) {
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

        auto bmp_data = bmp_file.data();
        auto pixels_data = bmp_data->pixels_data();
        auto bitcount = bmp_file.data()->bi_bitcount();

        auto result = std::make_shared<SOASpriteRGB>(bmp_data->width(), bmp_data->height());

        switch (bitcount) {
            case 8: {
                result->lock([&](auto w, auto h, auto rbuf, auto gbuf, auto bbuf) {
                    size_t d_offset = h * w - w;
                    size_t slide = w * 2;
                    size_t s_offset = 0;
                    for(size_t j = h; j; --j) {
                        for(size_t i = w; i ; --i) {
                            auto idx = static_cast<uint8_t>(pixels_data[s_offset++]);

                            bbuf[d_offset] = idx;
                            gbuf[d_offset] = idx;
                            rbuf[d_offset++] = idx;
                        }
                        d_offset -= slide;
                     }
                });
            } break;
            default: {
                LOG("unsupported bitcount detected");
                return std::make_tuple(true, std::make_shared<SOASpriteRGB>(1,1));
            }
        }
        return std::make_tuple(true, result);
    } catch (const std::exception& ex) {
        LOG_ERROR(ex.what());
        return std::make_tuple(false, std::make_shared<SOASpriteRGB>(1,1));
    }
}

std::tuple<bool, std::shared_ptr<Sprite16a>> ResourceFile::read_16a_shared(const char* path) {
    try {
        auto sprite_resource = get_resource(path);
        if(sprite_resource == nullptr) {
            LOG_ERROR("Resource not found");
            std::shared_ptr<Sprite16a> result{nullptr};
            return std::make_tuple(false, result);
        }
        auto bytes = sprite_resource->bytes();
        kaitai::kstream ks{bytes};
        rage_of_mages_1_16a_t sprite_file{&ks};
        auto result = std::make_shared<Sprite16a>(&sprite_file);
        return std::make_tuple(true, result);

    } catch (const std::exception& ex) {
        LOG_ERROR(ex.what());
        std::shared_ptr<Sprite16a> result{nullptr};
        return std::make_tuple(false, result);
    }
}

std::tuple<bool, std::shared_ptr<Sprite16>> ResourceFile::read_16_shared(const char* path) {
    try {
        auto sprite_resource = get_resource(path);
        if(sprite_resource == nullptr) {
            LOG_ERROR("Resource not found");
            std::shared_ptr<Sprite16> result{nullptr};
            return std::make_tuple(false, result);
        }
        auto bytes = sprite_resource->bytes();
        kaitai::kstream ks{bytes};
        rage_of_mages_1_16_t sprite_file{&ks};
        auto result = std::make_shared<Sprite16>(&sprite_file);
        return std::make_tuple(true, result);

    } catch (const std::exception& ex) {
        LOG_ERROR(ex.what());
        std::shared_ptr<Sprite16> result{nullptr};
        return std::make_tuple(false, result);
    }
}

std::tuple<bool, std::shared_ptr<Sprite256>> ResourceFile::read_256_shared(const char* path) {
    try {
        auto sprite_resource = get_resource(path);
        if(sprite_resource == nullptr) {
            LOG_ERROR("Resource not found");
            std::shared_ptr<Sprite256> result{nullptr};
            return std::make_tuple(false, result);
        }
        auto bytes = sprite_resource->bytes();
        kaitai::kstream ks{bytes};
        rage_of_mages_1_256_t sprite_file{&ks};
        auto result = std::make_shared<Sprite256>(&sprite_file);
        return std::make_tuple(true, result);

    } catch (...) {
        //LOG_ERROR(ex.what());
        std::shared_ptr<Sprite256> result{nullptr};
        return std::make_tuple(false, result);
    }
}

std::tuple<bool, std::shared_ptr<Font16>> ResourceFile::read_font_16_shared(const char* sprite_path, const char* gliph_data_path) {
    auto [sprite_loaded_successfully, sprite] = read_16_shared(sprite_path);
    if(!sprite_loaded_successfully) {
        LOG_ERROR("problem occured on loading of .16 file for font " << sprite_path);
        std::shared_ptr<Font16> res{nullptr};
        return std::make_tuple(false, res);
    }
    auto gliph_data_resource = get_resource(gliph_data_path);
    if(gliph_data_resource == nullptr) {
        LOG_ERROR("problem occured on loading of glyph width data: " << gliph_data_path);
        std::shared_ptr<Font16> res{nullptr};
        return std::make_tuple(false, res);
    }

    try {
        auto gliph_data = gliph_data_resource->bytes();
        kaitai::kstream ks{gliph_data};
        std::vector<uint16_t> glyph_width_storage;

        auto count = ks.size() / 4;
        glyph_width_storage.reserve(count);
        for(uint16_t i = 0; i < count; ++i) {
            glyph_width_storage.push_back(static_cast<uint16_t>(ks.read_u4le()));
        }

        return std::make_tuple(true, std::make_shared<Font16>(sprite, std::move(glyph_width_storage)));
    } catch(const std::exception& ex) {
        LOG_ERROR(ex.what());
        std::shared_ptr<Font16> res{nullptr};
        return std::make_tuple(false, res);
    }
}

std::tuple<bool, std::shared_ptr<Font16a>> ResourceFile::read_font_16a_shared(const char* sprite_path, const char* gliph_data_path) {
    auto [sprite_loaded_successfully, sprite] = read_16a_shared(sprite_path);
    if(!sprite_loaded_successfully) {
        LOG_ERROR("problem occured on loading of .16 file for font " << sprite_path);
        std::shared_ptr<Font16a> res{nullptr};
        return std::make_tuple(false, res);
    }
    auto gliph_data_resource = get_resource(gliph_data_path);
    if(gliph_data_resource == nullptr) {
        LOG_ERROR("problem occured on loading of glyph width data: " << gliph_data_path);
        std::shared_ptr<Font16a> res{nullptr};
        return std::make_tuple(false, res);
    }

    try {
        auto gliph_data = gliph_data_resource->bytes();
        kaitai::kstream ks{gliph_data};
        std::vector<uint16_t> glyph_width_storage;

        auto count = ks.size() / 4;
        glyph_width_storage.reserve(count);
        for(uint16_t i = 0; i < count; ++i) {
            glyph_width_storage.push_back(static_cast<uint16_t>(ks.read_u4le()));
        }

        return std::make_tuple(true, std::make_shared<Font16a>(sprite, std::move(glyph_width_storage)));

    } catch(const std::exception& ex) {
        LOG_ERROR(ex.what());
        std::shared_ptr<Font16a> res{nullptr};
        return std::make_tuple(false, res);
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

        auto bmp_data = bmp_file.data();
        auto pixels_data = bmp_data->pixels_data();

        auto bitcount = bmp_data->bi_bitcount();

        auto result = std::make_shared<SOASpriteRGB>(bmp_data->width(), bmp_data->height());

        switch (bitcount) {
            case 8: {
                auto palette = *(bmp_data->palette());
                result->lock([&](auto w, auto h, auto rbuf, auto gbuf, auto bbuf) {
                    size_t d_offset = h * w - w;
                    size_t slide = w * 2;
                    size_t s_offset = 0;
                    for(size_t j = h; j; --j) {
                        for(size_t i = w; i ; --i) {
                            auto idx = static_cast<uint8_t>(pixels_data[s_offset++]);
                            auto clr = palette[idx];

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
                        d_offset -= slide;
                     }
                });
            } break;
            case 24: {
                result->lock([&](auto w, auto h, auto rbuf, auto gbuf, auto bbuf) {
                    size_t d_offset = h * w - w;
                    size_t slide = w * 2;
                    size_t s_offset = 0;
                    for(size_t j = h; j; --j) {
                        for(size_t i = w; i ; --i) {
                            bbuf[d_offset] = static_cast<uint8_t>(pixels_data[s_offset++]);
                            gbuf[d_offset] = static_cast<uint8_t>(pixels_data[s_offset++]);
                            rbuf[d_offset++] = static_cast<uint8_t>(pixels_data[s_offset++]);
                        }
                        d_offset -= slide;
                     }
                });
            } break;
            default: {
                LOG("unsupported bitcount detected");
                return std::make_tuple(true, std::make_shared<SOASpriteRGB>(1,1));
            }
        }
        return std::make_tuple(true, result);
    } catch (const std::exception& ex) {
        LOG_ERROR(ex.what());
        return std::make_tuple(false, std::make_shared<SOASpriteRGB>(1,1));
    }
}

ResourceFile::~ResourceFile() {
    if(resource_file_nodes_ != nullptr) delete resource_file_nodes_;
    if(kaitai_stream_ != nullptr) delete kaitai_stream_;
    if(in_file_stream_ != nullptr) delete in_file_stream_;
}


