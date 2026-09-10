# Engine Design

How each milestone task is implemented in this engine, with exact file/class
references. See `README.md` for build instructions and how to consume this
as a library from another repo.

## Task 1: Core Graphics Setup

- **SDL3 init**: `src/core/main.cpp` calls `SDL_Init(SDL_INIT_VIDEO)` before
  constructing anything, and `SDL_Quit()` on the way out (success or
  exception).
- **Window**: `Window` (`src/core/Window.h`/`.cpp`) wraps `SDL_CreateWindow`
  behind an RAII type — the constructor throws `std::runtime_error` on
  failure, the destructor calls `SDL_DestroyWindow`. `Application` creates
  one at 1920x1080: `window_("Game Engine", 1920, 1080)`
  (`Application.cpp:16`).
- **Renderer**: `Renderer` (`src/core/Renderer.h`/`.cpp`) wraps
  `SDL_CreateRenderer` the same way, and exposes `clear(r, g, b, a)` /
  `present()`.
- **Main loop**: `Application::run()` (`Application.cpp:41-48`) loops
  `processEvents()` --> `update()` --> `render()` until a quit event or Escape
  is seen (`processEvents()`, `Application.cpp:53-63`).
- **Clears to blue, prepares, renders**: `Application::render()`
  (`Application.cpp:91-99`) calls `renderer_.clear(...)` (defaults to
  `(30, 60, 180)`, a blue — configurable per-game via
  `Application::setBackground(r, g, b)` rather than hard-coded), then draws
  every entity, then presents.
  (`Application.cpp:68-86`): it feeds input to the player, steps every
  entity, then resolves collisions.

## Task 2: Generic Entity System

- `Entity` (`src/entity/Entity.h`/`.cpp`) is the base class for anything the
  engine can update and draw. It only knows about **position**
  (`x_`, `y_`, local to an optional parent — `worldX()`/`worldY()` resolve
  the absolute position) and an optional **renderable**
  (`std::unique_ptr<Sprite> sprite_`, set via `setRenderAsset()`). It has no
  concept of "player" or "platform" or any specific game object.
- `Application` owns `std::vector<std::unique_ptr<Entity>> entities_` and
  calls `entity->update()` / `entity-->draw(renderer)` on all of them
  generically (`Application.cpp:74-76, 94-96`) — it never downcasts or
  switches on entity type.
- `Entity::update()`/`draw()` are `virtual`, so a game can subclass `Entity`
  for custom behavior (e.g. swapping sprites based on state) without the
  engine needing to know; `onCollision(Entity*)` and `movement()` are
  virtual hooks for the same reason. `addChild()` lets entities form a
  parent/child hierarchy (so moving a parent moves its children).

## Task 3: Physics System

- `Physics` (`src/physics/Physics.h`) exposes `setGravity(float)` /
  `getGravity() const`. The value is stored as
  `gravityWeight` shared across every `Physics()`
  instance, so `Physics().setGravity(value)` called once actually persists
  everywhere `Physics().getGravity()` is read later; it's a runtime value,
  never a hard-coded constant in the physics/entity code.
- Gravity is applied generically in `Entity::update()`
  (`Entity.cpp:15-21`):
  ```cpp
  if (hasPhysics_) {
      vy_ += Physics().getGravity();
      x_ += vx_;
      y_ += vy_;
  }
  ```
  Any entity opts in via `setHasPhysics(true)` — the engine doesn't need a
  separate "physics object" concept; physics is just an integration step
  every entity can enable.
- A game sets the strength via `Physics().setGravity(...)` — see
  `src/core/main.cpp:39` for the engine's own demo.

## Task 4: Input Handling System

- `Input` (`src/input/Input.h`/`.cpp`) reads keyboard state via
  `SDL_GetKeyboardState(nullptr)` (`Input.cpp:22`) — not SDL key-down/up
  events — and translates physical scancodes into the entity's velocity:
  `SDL_SCANCODE_LEFT`/`RIGHT` set horizontal velocity, `SDL_SCANCODE_SPACE`
  triggers a jump only `if (player-->isGrounded())` (`Input.cpp:34-37`).
- `Application::update()` calls `Input().keyPressed(player)` once per frame
  for whichever entity was registered via `Application::setPlayer()`
  (`Application.cpp:69-72`) — the engine doesn't hard-code which entity is
  controllable.

## Task 5: Collision Detection System

- `Collision::hasCollision(Entity* a, Entity* b)` (`Collision.cpp:12-26`)
  returns `bool`. It builds each entity's AABB via `Entity::hitbox()`
  (`Entity.cpp:43-45`, centered on the entity's world position) and calls
  `SDL_GetRectIntersectionFloat` — SDL3's equivalent of `SDL_HasIntersection`,
  returning both the yes/no overlap result and the overlap rect.
- It's generic over any two `Entity*`; `Application::update()` calls it for
  the player against every other visible entity (`Application.cpp:78-84`).
- Two response modes, both driven by data on `Entity` rather than special
  cases in `Collision`:
  - **Solid** (default): `collisionResponse()` (`Collision.cpp:28-46`)
    pushes the entities apart along the axis of least overlap, zeroes the
    relevant velocity component, and sets `grounded` when landing on top of
    something — this is what makes platforms walkable.
  - **Trigger**: an entity with `setTrigger(true)` skips
    `collisionResponse()` entirely (`Collision.cpp:18`) but still fires
    `onCollision()` on both sides. This is how game-specific "touch to
    collect" or "touch to win" logic (e.g. a totem or goal) is built on top
    of the engine without `Collision` or `Entity` knowing what a totem is.
