#ifndef GAMEENGINE_WINDOW_H
#define GAMEENGINE_WINDOW_H

#include <SDL3/SDL.h>

#endif //GAMEENGINE_WINDOW_H

class Window {
public:
    Window(const char* title, int width, int height);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    SDL_Window* handle() const { return window_; }

private:
    SDL_Window* window_ = nullptr;
};
