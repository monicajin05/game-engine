# game-engine

2D game engine built for CSC481.

## Structure

```
src/
├── core/       # SDL init, window/renderer creation, main loop
├── entity/     # Generic entity/game object system
├── physics/    # Gravity and other physics behaviors
├── input/      # Keyboard input handling
├── collision/  # Bounding-box collision detection
└── render/     # Rendering helpers
assets/         # Textures, sprites, etc.
```

## Build

Requires SDL3 and CMake.

```
cmake -B build
cmake --build build
```
