#include "Application.h"

#include "entity/SpriteEntity.h"
#include "render/Sprite.h"

#include <SDL3/SDL.h>

/**
 * @author mjin6
 */

namespace {
// Spritesheet layout constants taken from CSC481-581-M1/src/main.cpp:6-10.
constexpr int kFrameCount = 6;
constexpr int kFrameWidth = 32;
constexpr int kFrameHeight = 32;
constexpr int kSpriteScale = 8;
constexpr int kAnimationDelay = 10;
}  // namespace

/**
 * Constructs an Application with a window, renderer, and the scene's entities.
 * @throws std::runtime_error if a sprite texture fails to load.
 */
Application::Application()
    : window_("Game Engine", 1920, 1080)
    , renderer_(window_) {
    int width = 0;
    int height = 0;
    SDL_GetRenderOutputSize(renderer_.handle(), &width, &height);

    auto sprite = std::make_unique<Sprite>(
        renderer_.handle(), "assets/darkworld_enemy_skullduggery_idle.png",
        kFrameWidth, kFrameHeight, kFrameCount, kAnimationDelay, kSpriteScale);
    entities_.push_back(std::make_unique<SpriteEntity>(
        width / 2.0f, height / 2.0f, std::move(sprite)));
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
    }
}

/**
 * Update every entity in the scene.
 */
void Application::update() {
    for (auto& entity : entities_) {
        entity->update();
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
