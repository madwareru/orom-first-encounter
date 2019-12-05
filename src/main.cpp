#include <vector>

#include <util/defer_action.h>
#include <util/macro_shared.h>

#include <windowing/window.h>
#include <game/game.h>

int main(int argc, char** argv) {
    if(argc > 1) {
        for(int i = 1; i < argc; ++i) {
            std::string param{argv[i]};
            if(param.compare("windowed") == 0) {
                Game::windowed = true;
            }
            else if(param.compare("800") == 0) {
                Game::window_width = 800;
                Game::window_height = 600;
            }
            else if(param.compare("640") == 0) {
                Game::window_width = 640;
                Game::window_height = 480;
            }
            else if(param.compare("1280") == 0) {
                Game::window_width = 1280;
                Game::window_height = 768;
            }
        }
    }

    Game::GameStage::terrain_cache = new uint8_t[4 * Game::window_width * Game::window_height];
    DEFER([&]() {delete [] Game::GameStage::terrain_cache; })

    WindowCreationParams window_params {
        "Open Rage Of Mages", // title
        Game::window_width,   // width
        Game::window_height,  // height
        !Game::windowed,      // fullscreen
        0x07, 0x02, 0x13      // clear color
    };

    Game::clear_r = window_params.clear_color_r;
    Game::clear_g = window_params.clear_color_g;
    Game::clear_b = window_params.clear_color_b;

    LifetimeProcHolder lifetime_procs {
        Game::init,
        Game::update,
        Game::render
    };

    using callback_holder = std::variant<
        KeyCallbackHolder,
        CursorPosCallbackHolder,
        MouseButtonCallbackHolder>;

    std::vector<callback_holder> event_callbacks;
    event_callbacks.emplace_back(KeyCallbackHolder{Game::key_callback});
    event_callbacks.emplace_back(CursorPosCallbackHolder{Game::mouse_callback});
    event_callbacks.emplace_back(MouseButtonCallbackHolder{Game::mouse_button_callback});

    if(!glfwInit()) {
        return 1;
    }

    Game::glfw_window = INIT_WINDOW(window_params);

    if(!Game::glfw_window) {
        return 1;
    }

    DEFER([&](){ glfwDestroyWindow(Game::glfw_window); })

    if(!start_main_loop(
        Game::glfw_window,
        window_params,
        lifetime_procs,
        event_callbacks
    )) return 1;

    return 0;
}
