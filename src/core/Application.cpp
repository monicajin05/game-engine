#include "Application.h"

#include <SDL3/SDL.h>

Application::Application()
    : window_("Game Engine", 1920, 1080)
    , renderer_(window_) {
}

void Application::run() {
    while (running_) {
        processEvents();
        update();
        render();
    }
}

void Application::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running_ = false;
        }
    }
}

void Application::update() {
}

void Application::render() {
    renderer_.clear(30, 60, 180, 255);
    renderer_.present();
}
