#include "Input.h"

#include <SDL3/SDL.h>
#include "core/Application.h"
#include "entity/Entity.h"
#include "physics/Physics.h"

/**
 * @author bacrawfo
 */
namespace {
    constexpr int up = SDL_SCANCODE_W;
    constexpr int left = SDL_SCANCODE_A;
    constexpr int right = SDL_SCANCODE_D;
    constexpr int esc = SDL_SCANCODE_ESCAPE;

    constexpr int kFrameCount = 6;
    constexpr int kFrameWidth = 32;
    constexpr int kFrameHeight = 32;
    constexpr int kSpriteScale = 8;
    constexpr int kAnimationDelay = 20;
}

/**
 * Function that defines behaviors when a key has been pressed.
 * Takes key value and performs actions if the value matches one of the assigned keys.
 */
bool Input::keyPressed(Entity* player) {
    const bool* keys = SDL_GetKeyboardState(nullptr);
    if (moving) {
        if (!keys[left] && !keys[right]) {
            return keyReleased(left, player);
        }
    } else {
        if (keys[up]) {
            player->setPosition(player->x(), player->y() + 32);
            player->setVelocity(player->velocityX(), Physics().getGravity());
        }

        if (keys[left]) {
            player->setVelocity(player->velocityX() - 4, player->velocityY());
            moving = true;
        }

        if (keys[right]) {
            player->setVelocity(player->velocityX() + 4, player->velocityY());
            moving = true;
        }

        if (keys[esc]) {
            SDL_Quit();
        }
    }

    return true;
}

/**
 * Function that defines behaviors when a key stops being pressed.
 * Takes key value and performs actions.
 */
bool Input::keyReleased(int key, Entity* player) {
    player->setVelocity(0, player->velocityY());
    moving = false;

    return true;
}