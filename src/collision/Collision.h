#ifndef GAMEENGINE_COLLISION_H
#define GAMEENGINE_COLLISION_H

#include "entity/Entity.h"

#include <SDL3/SDL.h>

class Collision {
    public:

    void hasCollision(Entity* a, Entity* b);

    void collisionResponse(const SDL_FRect &hitboxA, const SDL_FRect &hitboxB, const SDL_FRect &overlap, Entity *a, Entity *b);

    const int windowWidth = 1920;
    const int windowHeight = 1080;
};

#endif //GAMEENGINE_COLLISION_H