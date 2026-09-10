#include "Input.h"

#include <SDL3/SDL.h>
#include "core/Application.h"
#include "entity/Entity.h"
#include "physics/Physics.h"

/**
 * @author bacrawfo
 */
namespace {
    constexpr int jump = SDL_SCANCODE_SPACE;
    constexpr int left = SDL_SCANCODE_LEFT;
    constexpr int right = SDL_SCANCODE_RIGHT;
}

/**
 * Function that defines behaviors when a key has been pressed.
 * Takes key value and performs actions if the value matches one of the assigned keys.
 */
bool Input::keyPressed(Entity* player) {
    const bool* keys = SDL_GetKeyboardState(nullptr);
    constexpr float speed = 7.0f;

    float horizontalVelocity = 0.0f;
    if (keys[left]) {
        horizontalVelocity -= speed;
    }
    if (keys[right]) {
        horizontalVelocity += speed;
    }
    player->setVelocity(horizontalVelocity, player->velocityY());

    if (keys[jump] && player->isGrounded()) {
        player->setVelocity(player->velocityX(), -13.0f);
        player->setGrounded(false);
    }

    return true;
}

/**
 * Function that defines behaviors when a key stops being pressed.
 * Takes key value and performs actions.
 */
bool Input::keyReleased(int key, Entity* player) {
    player->setVelocity(0.0f, player->velocityY());
    return true;
}