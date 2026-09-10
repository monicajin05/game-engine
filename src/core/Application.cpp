#include "Application.h"

#include "input/Input.h"
#include "collision/Collision.h"
#include <SDL3/SDL.h>

/**
 * @author mjin6
 */

/**
 * Constructs an Application with a window and renderer. The scene starts
 * empty; use addEntity()/setPlayer() to populate it.
 */
Application::Application()
    : window_("Game Engine", 1920, 1080)
    , renderer_(window_) {
}

void Application::addEntity(std::unique_ptr<Entity> entity) {
    entities_.push_back(std::move(entity));
}

void Application::setPlayer(Entity* player) {
    entity_player = player;
}

void Application::getRenderSize(int& width, int& height) const {
    SDL_GetRenderOutputSize(renderer_.handle(), &width, &height);
}

/**
 * Run the application loop, which processes events, updates entities, and renders the scene.
 */
void Application::run() {
    while (running_) {
        processEvents();
        update();
        render();
    }
}

/**
 * Processes SDL events, setting the running flag to false if a quit event is received.
 */
void Application::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running_ = false;
        }
        if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
            running_ = false;
        }
    }
}

/**
 * Update every entity in the scene.
 */
void Application::update() {
    Entity* player = getPlayer();
    if (player) {
        Input().keyPressed(player);
    }

    for (auto& entity : entities_) {
        entity->update();
        if (player && entity.get() != player) {
            Collision().hasCollision(player, entity.get());
        }
    }
}

/**
 * Draw every entity in the scene.
 */
void Application::render() {
    renderer_.clear(30, 60, 180, 255);

    for (auto& entity : entities_) {
        entity->draw(renderer_.handle());
    }

    renderer_.present();
}
