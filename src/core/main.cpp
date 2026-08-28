#include "Application.h"

#include <SDL3/SDL.h>

#include <exception>

/**
 * @author mjin6
 */

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    int result = 0;
    try {
        Application app;
        app.run();
    } catch (const std::exception& e) {
        SDL_Log("Fatal error: %s", e.what());
        result = 1;
    }

    SDL_Quit();
    return result;
}
