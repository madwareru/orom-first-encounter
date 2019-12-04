#ifndef RESOURCE_FILE_H
#define RESOURCE_FILE_H

#include <fstream>
#include <kaitaistruct.h>
#include <loaders/ksy/rage_of_mages_1_res.h>
#include <loaders/registry_file.h>
#include <tuple>
#include <memory>
#include <graphics/soaspritergb.h>
#include <graphics/Sprite16a.h>
#include <graphics/Sprite16.h>
#include <graphics/font_rendering.h>
#include <util/defer_action.h>

struct ResourceFile
{
    ResourceFile(const char* fileName);

    ResourceFile(const ResourceFile&) = delete;
    ResourceFile& operator=(const ResourceFile&) = delete;
    ResourceFile(ResourceFile&&) = delete;
    ResourceFile& operator=(ResourceFile&&) = delete;

    rage_of_mages_1_res_t::file_resource_t* get_resource(const char* path);

    std::tuple<bool, std::shared_ptr<Sprite16a>> read_16a_shared(const char* path);
    std::tuple<bool, std::shared_ptr<Sprite16>> read_16_shared(const char* path);
    std::tuple<bool, std::shared_ptr<Font16>> read_font_16_shared(const char* sprite_path, const char* gliph_data_path);
    std::tuple<bool, std::shared_ptr<Font16a>> read_font_16a_shared(const char* sprite_path, const char* gliph_data_path);

    std::tuple<bool, std::shared_ptr<SOASpriteRGB>> read_bmp_shared(const char* path);
    std::tuple<bool, std::shared_ptr<SOASpriteRGB>> read_mask_shared(const char* path);

    std::tuple<bool, std::unique_ptr<RegistryFile>> read_registry_res_unique(const char* path);
    std::tuple<bool, std::shared_ptr<RegistryFile>> read_registry_res_shared(const char* path);

    ~ResourceFile();
private:
    std::ifstream* in_file_stream_{nullptr};
    kaitai::kstream* kaitai_stream_{nullptr};
    rage_of_mages_1_res_t* resource_file_nodes_{nullptr};
};

#endif // RESOURCE_FILE_H
