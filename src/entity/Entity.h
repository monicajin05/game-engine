#ifndef GAMEENGINE_ENTITY_H
#define GAMEENGINE_ENTITY_H

#include "render/Sprite.h"
#include <SDL3/SDL.h>
#include <string>
using namespace std;

#include <memory>
#include <vector>

/** Base class for anything the engine can update and draw.
 *
 * Position is local to the parent entity (or the world origin, if there is
 * no parent) so that moving a parent moves its children with it; use
 * worldX()/worldY() to resolve the absolute position.
 * @author mjin6
*/
class Entity {
public:
    Entity(string id, float x, float y, float width = 0.0f, float height = 0.0f);
    virtual ~Entity() = default;

    virtual void update();
    virtual void draw(SDL_Renderer* renderer) const;
    virtual void onCollision(Entity* other) {}

    // Overridden by subclasses to set velocity from input/AI
    // physics integrates that velocity into position each frame.
    virtual void movement() {}

    float x() const { return x_; }
    float y() const { return y_; }
    void setPosition(float x, float y) { x_ = x; y_ = y; }
    float worldX() const { return parent_ ? parent_->worldX() + x_ : x_; }
    float worldY() const { return parent_ ? parent_->worldY() + y_ : y_; }

    float width() const { return width_; }
    float height() const { return height_; }
    void setSize(float width, float height) { width_ = width; height_ = height; }
    SDL_FRect hitbox() const;

    bool visible() const { return visible_; }
    void setVisible(bool visible) { visible_ = visible; }

    bool hasPhysics() const { return hasPhysics_; }
    void setHasPhysics(bool hasPhysics) { hasPhysics_ = hasPhysics; }

    bool isTrigger() const { return isTrigger_; }
    void setTrigger(bool isTrigger) { isTrigger_ = isTrigger; }

    bool isGrounded() const { return grounded_; }
    void setGrounded(bool grounded) { grounded_ = grounded; }

    float velocityX() const { return vx_; }
    float velocityY() const { return vy_; }
    void setVelocity(float vx, float vy) { vx_ = vx; vy_ = vy; }

    void setRenderAsset(std::unique_ptr<Sprite> sprite) { sprite_ = std::move(sprite); }
    Sprite* renderAsset() const { return sprite_.get(); }

    Entity* parent() const { return parent_; }
    const std::vector<std::unique_ptr<Entity>>& children() const { return children_; }
    Entity& addChild(std::unique_ptr<Entity> child);
    string getId() {return id;};

protected:
    float x_;
    float y_;
    float width_;
    float height_;
    bool visible_ = true;
    bool hasPhysics_ = false;
    bool isTrigger_ = false;
    bool grounded_ = false;
    float vx_ = 0.0f;
    float vy_ = 0.0f;
    std::unique_ptr<Sprite> sprite_;
    Entity* parent_ = nullptr;
    std::vector<std::unique_ptr<Entity>> children_;
    string id;
};

#endif //GAMEENGINE_ENTITY_H