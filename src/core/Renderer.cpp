#include "Renderer.h"

#include "Window.h"

#include <stdexcept>
#include <string>

Renderer::Renderer(Window& window) {
    renderer_ = SDL_CreateRenderer(window.handle(), nullptr);
    if (!renderer_) {
        throw std::runtime_error(std::string("SDL_CreateRenderer failed: ") + SDL_GetError());
    }
}

Renderer::~Renderer() {
    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
    }
}

void Renderer::clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer_, r, g, b, a);
    SDL_RenderClear(renderer_);
}

void Renderer::present() {
    SDL_RenderPresent(renderer_);
}
