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

    // Hands ownership of an entity to the scene; it will be updated and
    // drawn every frame from now on.
    void addEntity(std::unique_ptr<Entity> entity);

    // Marks an already-added entity as the one Input drives and Collision
    // checks everything else against. Pass nullptr for a scene with no
    // player-controlled entity.
    void setPlayer(Entity* player);
    Entity* getPlayer() {return entity_player;};

    // Colour the scene is cleared to each frame, so a game can pick its own
    // backdrop instead of the engine's default.
    void setBackground(Uint8 r, Uint8 g, Uint8 b);

    SDL_Renderer* rendererHandle() const { return renderer_.handle(); }

    // Render output size in pixels. Prefer this over SDL_GetWindowSize()
    // for positioning entities: window size is DPI-scaled and can differ
    // from the renderer's actual pixel coordinate space.
    void getRenderSize(int& width, int& height) const;

private:
    void processEvents();
    void update();
    void render();

    Window window_;
    Renderer renderer_;
    std::vector<std::unique_ptr<Entity>> entities_;
    bool running_ = true;
    Entity* entity_player = nullptr;
    Uint8 backgroundR_ = 30;
    Uint8 backgroundG_ = 60;
    Uint8 backgroundB_ = 180;
};

#endif //GAMEENGINE_APPLICATION_H