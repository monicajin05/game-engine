#include "Collision.h"

#include "core/Application.h"
#include "entity/Entity.h"
#include "physics/Physics.h"
#include <SDL3/SDL.h>
#include <string>

/**
 * @author bacrawfo
 */
void Collision::hasCollision(Entity* a, Entity* b) {
    SDL_FRect hitboxA = a->hitbox();
    SDL_FRect hitboxB = b->hitbox();
    SDL_FRect overlap {0};

    if (SDL_GetRectIntersectionFloat(&hitboxA, &hitboxB, &overlap)) {
        collisionResponse(hitboxA, hitboxB, overlap, a, b);
    }
}

void Collision::collisionResponse(const SDL_FRect &hitboxA, const SDL_FRect &hitboxB, const SDL_FRect &overlap, Entity* a, Entity* b) {
    if (overlap.w < overlap.h) {
        if (a->velocityX() > 0) {
            a->setPosition(a->x() - overlap.w, a->y());
        } else if (a->velocityX() < 0) {
            a->setPosition(a->x() + overlap.w, a->y());
        }
        a->setVelocity(0, a->velocityY());
    } else {
        if (a->velocityY() > 0) {
            a->setPosition(a->x(), a->y() - overlap.h);
            a->setVelocity(a->velocityX(), Physics().getGravity());
        } else if (a->velocityY() < 0) {
            a->setPosition(a->x(), a->y() + overlap.h);
            a->setVelocity(a->velocityX(), 0);
        }
    }
}