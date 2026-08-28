#pragma once

#include "Renderer.h"
#include "Window.h"
#include "entity/Entity.h"

#include <memory>
#include <vector>

/**
 * Creates a window and renderer, owns the scene's entities, and runs a game loop.
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
    std::vector<std::unique_ptr<Entity>> entities_;
    bool running_ = true;
};
