#pragma once

#include "Renderer.h"
#include "Window.h"

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
    bool running_ = true;
};
