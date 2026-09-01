#pragma once

#include "Entity.h"
#include "render/Sprite.h"

#include <memory>

// An Entity rendered as an animated spritesheet
class SpriteEntity : public Entity {
public:
    // center position of entity
    SpriteEntity(float x, float y, std::unique_ptr<Sprite> sprite);

    void update() override;
    void draw(SDL_Renderer* renderer) const override;

private:
    std::unique_ptr<Sprite> sprite_;
};
