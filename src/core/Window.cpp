#include "Window.h"

#include <stdexcept>
#include <string>

/**
 * Constructs a Window with the given title, width, and height.
 * @author mjin6
 */

Window::Window(const char* title, int width, int height) {
    window_ = SDL_CreateWindow(title, width, height, 0);
    if (!window_) {
        throw std::runtime_error(std::string("SDL_CreateWindow failed: ") + SDL_GetError());
    }
}

Window::~Window() {
    if (window_) {
        SDL_DestroyWindow(window_);
    }
}
