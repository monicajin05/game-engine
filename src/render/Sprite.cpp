#include "Sprite.h"

#include <SDL3_image/SDL_image.h>

#include <stdexcept>
#include <string>

/**
 * Loads a spritesheet as a looping animation.
 * @author mjin6
 */
Sprite::Sprite(SDL_Renderer* renderer, const char* path, int frameWidth, int frameHeight,
               int frameCount, int animationDelay, int scale)
    : frameWidth_(frameWidth)
    , frameHeight_(frameHeight)
    , frameCount_(frameCount)
    , animationDelay_(animationDelay)
    , scale_(scale) {
    // Taken from CSC481-581-M1/src/main.cpp:34.
    texture_ = IMG_LoadTexture(renderer, path);
    if (!texture_) {
        throw std::runtime_error(std::string("IMG_LoadTexture failed: ") + SDL_GetError());
    }
}

Sprite::~Sprite() {
    if (texture_) {
        SDL_DestroyTexture(texture_);
    }
}

void Sprite::update() {
    // Frame-advance timing taken from CSC481-581-M1/src/main.cpp:69-73.
    lastFrameTime_ += 1;
    if (lastFrameTime_ >= static_cast<Uint32>(animationDelay_)) {
        currentFrame_ = (currentFrame_ + 1) % frameCount_;
        lastFrameTime_ = 0;
    }
}

void Sprite::draw(SDL_Renderer* renderer, float centerX, float centerY) const {
    // Source/destination rect construction taken from
    // CSC481-581-M1/src/main.cpp:89-106.
    SDL_FRect srcRect = {
        static_cast<float>(currentFrame_ * frameWidth_),
        0.0f,
        static_cast<float>(frameWidth_),
        static_cast<float>(frameHeight_)
    };

    SDL_FRect dstRect = {
        centerX - (frameWidth_ * scale_) / 2.0f,
        centerY - (frameHeight_ * scale_) / 2.0f,
        static_cast<float>(frameWidth_ * scale_),
        static_cast<float>(frameHeight_ * scale_)
    };

    SDL_RenderTexture(renderer, texture_, &srcRect, &dstRect);
}
