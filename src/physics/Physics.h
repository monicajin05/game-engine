#ifndef GAMEENGINE_PHYSICS_H
#define GAMEENGINE_PHYSICS_H

/**
 * Class for containing functions related to physics
 * Taken from CSC481-581-M3/src/physics.h
 */
class Physics {
    public:
    Physics() = default;

    //Use these functions to set and get the gravity variable to apply to entities
    void setGravity(const float gravity) { gravityWeight = gravity; }
    float getGravity() const { return gravityWeight; }

    private:
    inline static float gravityWeight = 0.45f;
};

#endif //GAMEENGINE_PHYSICS_H