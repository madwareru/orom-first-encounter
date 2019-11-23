#include <vector>

#include <util/defer_action.h>
#include <util/macro_shared.h>

#include <windowing/window.h>
#include <game/game.h>

int main() {
    WindowCreationParams window_params {
        "Open Rage Of Mages", // title
        1024,                 // width
        768,                  // height
        false,                // fullscreen
        0x07, 0x02, 0x13      // clear color
    };

    LifetimeProcHolder lifetime_procs {
        Game::init,
        Game::update,
        Game::render
    };

    using callback_holder = std::variant<
        KeyCallbackHolder,
        CursorPosCallbackHolder,
        MouseButtonCallbackHolder>;

    std::vector<callback_holder> eventCallbacks;

    if(!glfwInit()) {
        return 1;
    }

    GLFWwindow* glfw_window = INIT_WINDOW(window_params);

    if(!glfw_window) {
        return 1;
    }

    DEFER([&](){ glfwDestroyWindow(glfw_window); })

    if(!start_main_loop(
        glfw_window,
        window_params,
        lifetime_procs,
        eventCallbacks
    )) return 1;

    return 0;
}
