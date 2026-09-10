#ifndef GAMEENGINE_PHYSICS_H
#define GAMEENGINE_PHYSICS_H

/**
 * Class for containing functions related to physics
 * Taken from CSC481-581-M3/src/physics.h
 */
class Physics {
    public:
    Physics() {};

    //Use these functions to set and get the gravity variable to apply to entities
    void setGravity(const int gravity) {gravityWeight = gravity;};
    int getGravity() {return gravityWeight;};

    private:
    int gravityWeight;
};

#endif //GAMEENGINE_PHYSICS_H