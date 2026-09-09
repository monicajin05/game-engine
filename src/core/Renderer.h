#ifndef GAMEENGINE_RENDERER_H
#define GAMEENGINE_RENDERER_H

#include <SDL3/SDL.h>

class Window;

class Renderer {
public:
    explicit Renderer(Window& window);
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    void clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
    void present();

    SDL_Renderer* handle() const { return renderer_; }

private:
    SDL_Renderer* renderer_ = nullptr;
};

#endif //GAMEENGINE_RENDERER_H