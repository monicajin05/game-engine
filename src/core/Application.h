#ifndef GAMEENGINE_APPLICATION_H
#define GAMEENGINE_APPLICATION_H

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

    Entity* getPlayer() {return entity_player;};

private:
    void processEvents();
    void update();
    void render();

    Window window_;
    Renderer renderer_;
    std::vector<std::unique_ptr<Entity>> entities_;
    bool running_ = true;
    Entity* entity_player = nullptr;
};

#endif //GAMEENGINE_APPLICATION_H