#ifndef GAMEENGINE_SPRITE_H
#define GAMEENGINE_SPRITE_H

#include <SDL3/SDL.h>

// Loads a spritesheet as a looping animation
//
// Texture loading, frame-advance timing, and the source/destination rect
// math are taken from the CSC481 boilerplate provided in class:
// "M2 Class Activity/CSC481-581-M1/src/main.cpp" (lines 34, 69-73, 89-106).
// @author mjin6
class Sprite {
public:
    Sprite(SDL_Renderer* renderer, const char* path, int frameWidth, int frameHeight,
           int frameCount, int animationDelay, int scale = 1);
    ~Sprite();

    Sprite(const Sprite&) = delete;
    Sprite& operator=(const Sprite&) = delete;

    void update();

    /**
     * Draws the sprite centered at the given coordinates.
     */
    void draw(SDL_Renderer* renderer, float centerX, float centerY) const;

private:
    SDL_Texture* texture_ = nullptr;
    int frameWidth_;
    int frameHeight_;
    int frameCount_;
    int animationDelay_;
    int scale_;
    int currentFrame_ = 0;
    Uint32 lastFrameTime_ = 0;
};

#endif //GAMEENGINE_SPRITE_H