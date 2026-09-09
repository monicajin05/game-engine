#ifndef GAMEENGINE_INPUT_H
#define GAMEENGINE_INPUT_H

#include <SDL3/SDL.h>
#include "entity/Entity.h"

/**
 * Class that handles user input
 * Taken from CSC481-581-M3/src/physics.h
 */
class Input {
    public:
        Input() {};
        virtual ~Input() = default;

    //Use these functions, or similar functions, to provide abstract remappable keyboard input
    //Create Key IDs, which allow you to call keyPressed using an abstract game concept (e.g. left) instead of the key itself in the game
    //In this input handler, you'll need to convert the abstract game concept to the physical key you poll from SDL_GetKeyboardState
    //Returns the boolean received from SDL_GetKeyboardState
        bool keyPressed(Entity* player);
        bool keyReleased(int key, Entity* player);

        bool moving = false;
};

#endif //GAMEENGINE_INPUT_H