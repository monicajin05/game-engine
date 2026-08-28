#include "SpriteEntity.h"

SpriteEntity::SpriteEntity(float x, float y, std::unique_ptr<Sprite> sprite)
    : Entity(x, y)
    , sprite_(std::move(sprite)) {
}

void SpriteEntity::update() {
    sprite_->update();
}

void SpriteEntity::draw(SDL_Renderer* renderer) const {
    sprite_->draw(renderer, x_, y_);
}
