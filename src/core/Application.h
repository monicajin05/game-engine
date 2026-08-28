#pragma once

#include "Renderer.h"
#include "Window.h"
#include "render/Sprite.h"

#include <memory>

/**
 * Creates a window, renderer, and sprite, and runs a game loop.
 * @author mjin6
 */

class Application {
public:
    Application();

    void run();

private:
    void processEvents();
    void update();
    void render();

    Window window_;
    Renderer renderer_;
    std::unique_ptr<Sprite> sprite_;
    bool running_ = true;
};
