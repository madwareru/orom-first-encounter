#include <game/shared/shared_res.h>
#include <loaders/resource_file.h>

namespace  {
    const char* GRAPHICS_RES_FILENAME = "GRAPHICS.res";
    const char* MAIN_RES_FILENAME     = "MAIN.res";
    const char* MOVIES_RES_FILENAME   = "MOVIES.res";
    const char* SCENARIO_RES_FILENAME = "SCENARIO.res";
    const char* SFX_RES_FILENAME      = "SFX.res";
    const char* SPEECH_RES_FILENAME   = "SPEECH.res";
    const char* WORLD_RES_FILENAME    = "WORLD.res";
}

namespace Game {
namespace Resources {
    #define RES_DEFINITION(res_name, res_file_name)     \
        ResourceFile& res_name() {                      \
            static ResourceFile resFile{res_file_name}; \
            return resFile;                             \
        }

    RES_DEFINITION(Graphics, GRAPHICS_RES_FILENAME);
    RES_DEFINITION(Main, MAIN_RES_FILENAME);
    RES_DEFINITION(Movies, MOVIES_RES_FILENAME);
    RES_DEFINITION(Scenario, SCENARIO_RES_FILENAME);
    RES_DEFINITION(Sfx, SFX_RES_FILENAME);
    RES_DEFINITION(Speech, SPEECH_RES_FILENAME);
    RES_DEFINITION(World, WORLD_RES_FILENAME);

    #undef RES_DEFINITION
}
}
