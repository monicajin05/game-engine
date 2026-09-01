#pragma once

#include <SDL3/SDL.h>

/** Base class for anything the engine can update and draw
 * @author mjin6
*/ 

class Entity {
public:
    Entity(float x, float y) : x_(x), y_(y) {}
    virtual ~Entity() = default;

    virtual void update() {}
    virtual void draw(SDL_Renderer* renderer) const = 0;

    float x() const { return x_; }
    float y() const { return y_; }
    void setPosition(float x, float y) { x_ = x; y_ = y; }

protected:
    float x_;
    float y_;
};
