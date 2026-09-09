#include "Application.h"

#include "render/Sprite.h"
#include "physics/Physics.h"
#include "input/Input.h"
#include "collision/Collision.h"
#include <SDL3/SDL.h>
#include <string>
using namespace std;

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

    Physics().setGravity(-9.8);

    /*
    auto sprite_skull = std::make_unique<Sprite>(
        renderer_.handle(), "assets/darkworld_enemy_skullduggery_idle.png",
        kFrameWidth, kFrameHeight, kFrameCount, kAnimationDelay, kSpriteScale);
    auto entity_skull = std::make_unique<Entity>(
        width / 2.0f, height / 2.0f,
        kFrameWidth * kSpriteScale, kFrameHeight * kSpriteScale);
    entity_skull->setRenderAsset(std::move(sprite_skull));
    entities_.push_back(std::move(entity_skull));
    */

    auto sprite_platform = std::make_unique<Sprite>(
        renderer_.handle(), "assets/darkworld_platform_mossystones_idle.png",
        kFrameWidth, kFrameHeight, kFrameCount, kAnimationDelay, kSpriteScale);
    auto entity_platform = std::make_unique<Entity>("platform",
        width / 2.0f, height / 2.0f - 32,
        kFrameWidth * kSpriteScale, kFrameHeight * kSpriteScale);
    entity_platform->setRenderAsset(std::move(sprite_platform));
    entities_.push_back(std::move(entity_platform));

    auto sprite_player = std::make_unique<Sprite>(
        renderer_.handle(), "assets/darkworld_character_morwen_idle.png",
        kFrameWidth, kFrameHeight, kFrameCount, kAnimationDelay, kSpriteScale);
    auto player = std::make_unique<Entity>("player",
        width / 2.0f, height / 2.0f,
        kFrameWidth * kSpriteScale, kFrameHeight * kSpriteScale);
    player->setHasPhysics(true);
    player->setRenderAsset(std::move(sprite_player));
    entity_player = player.get();
    entities_.push_back(std::move(player));
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
    Entity* player = getPlayer();
    Input().keyPressed(player);

    for (auto& entity : entities_) {
        entity->update();
        if (entity->getId() != "player") {
            Collision().hasCollision(getPlayer(), entity.get());
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
