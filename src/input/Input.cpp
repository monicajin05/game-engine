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
    constexpr int down = SDL_SCANCODE_S;
    constexpr int right = SDL_SCANCODE_D;

    constexpr int kSpriteScale = 2;
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
        if (keys[up] && player->velocityY()==0) {
            player->setPosition(player->x(), player->y() - 8);
            player->setVelocity(player->velocityX(), player->velocityY() + Physics().getGravity());
        }

        if (keys[down]) {
            player->setPosition(player->x(), player->y() + 8);
        }

        if (keys[left]) {
            player->setPosition(player->x() - 8, player->y());
            moving = true;
        }

        if (keys[right]) {
            player->setPosition(player->x() + 8, player->y());
            moving = true;
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