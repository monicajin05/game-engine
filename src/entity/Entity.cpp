#include "Entity.h"

#include <string>
using namespace std;

/**
 * @author mjin6
 */

Entity::Entity(string id, float x, float y, float width, float height)
    : x_(x), y_(y), width_(width), height_(height) {}

void Entity::update() {
    movement();
    if (hasPhysics_) {
        x_ += vx_;
        y_ += vy_;
    }
    if (sprite_) {
        sprite_->update();
    }
    for (auto& child : children_) {
        child->update();
    }
}

void Entity::draw(SDL_Renderer* renderer) const {
    if (!visible_) {
        return;
    }
    if (sprite_) {
        sprite_->draw(renderer, worldX(), worldY());
    }
    for (auto& child : children_) {
        child->draw(renderer);
    }
}

// Position is the center of the entity
SDL_FRect Entity::hitbox() const {
    return SDL_FRect{worldX() - width_ / 2.0f, worldY() - height_ / 2.0f, width_, height_};
}

// function to add child entity to this entity
Entity& Entity::addChild(std::unique_ptr<Entity> child) {
    child->parent_ = this;
    children_.push_back(std::move(child));
    return *children_.back();
}
