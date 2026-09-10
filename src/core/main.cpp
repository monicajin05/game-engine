#include "Application.h"

#include "entity/Entity.h"
#include "physics/Physics.h"
#include "render/Sprite.h"

#include <SDL3/SDL.h>

#include <exception>
#include <memory>

/**
 * Demo scene showcasing the engine
 * @author mjin6
 */

namespace {
constexpr int kFrameCount = 6;
constexpr int kFrameWidth = 32;
constexpr int kFrameHeight = 32;
constexpr int kSpriteScale = 2;
constexpr int kAnimationDelay = 100;
}  // namespace

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    int result = 0;
    try {
        Application app;

        int width = 0;
        int height = 0;
        app.getRenderSize(width, height);

        Physics().setGravity(4);

        auto sprite_platform = std::make_unique<Sprite>(
            app.rendererHandle(), "assets/darkworld_platform_mossystones_idle.png",
            96, 32, 1, kAnimationDelay, kSpriteScale);
        auto entity_platform = std::make_unique<Entity>("platform",
            width / 2.0f, height / 2.0f + 200,
            96 * kSpriteScale, 32 * kSpriteScale);
        entity_platform->setRenderAsset(std::move(sprite_platform));
        app.addEntity(std::move(entity_platform));

        auto sprite_player = std::make_unique<Sprite>(
            app.rendererHandle(), "assets/darkworld_character_morwen_idle.png",
            64, 64, 1, kAnimationDelay, kSpriteScale);
        auto entity_player = std::make_unique<Entity>("player",
            width / 2.0f, height / 2.0f,
            64 * kSpriteScale, 64 * kSpriteScale);
        entity_player->setHasPhysics(true);
        entity_player->setRenderAsset(std::move(sprite_player));
        entity_player->setVelocity(0, Physics().getGravity());
        Entity* player = entity_player.get();
        app.addEntity(std::move(entity_player));
        app.setPlayer(player);

        app.run();
    } catch (const std::exception& e) {
        SDL_Log("Fatal error: %s", e.what());
        result = 1;
    }

    SDL_Quit();
    return result;
}
