# game-engine

2D game engine built for CSC481.

**See DESIGN.md for documentation.**

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

Requires MSYS2 MinGW64 with the following packages:

```
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-make \
          mingw-w64-x86_64-sdl3 mingw-w64-x86_64-sdl3-image
cmake .. && make
game_engine.exe
```

Run these from an **MSYS2 MinGW64** shell (not MSYS/UCRT64) so `gcc`/`cmake`
resolve to the mingw64 toolchain and `find_package` can locate the
pacman-installed SDL3/SDL3_image config files:

```
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
make
./game_engine
```

To drop the `-G "MinGW Makefiles"` flag, set it once via
`export CMAKE_GENERATOR="MinGW Makefiles"` in your shell profile (otherwise
CMake defaults to the Visual Studio generator if VS is also installed).

The build copies the MinGW runtime and SDL DLLs next to `game_engine.exe`,
so it can also be run outside the MSYS2 shell (double-clicked in Explorer,
or from cmd/PowerShell/VS Code).

## Using this as a library in another repo

`CMakeLists.txt` builds two targets: `game_engine_lib` (the engine — window,
renderer, entity system, physics, input, collision) and `game_engine` (a demo
executable in `src/core/main.cpp` that spawns a platform and a player entity
to showcase it). A separate game repo can depend on the engine without
copying any code:

1. Add this repo as a git submodule, e.g. `vendored/game-engine`:
   ```
   git submodule add https://github.com/monicajin05/game-engine.git vendored/game-engine
   ```
2. In your game's `CMakeLists.txt`:
   ```cmake
   add_subdirectory(vendored/game-engine EXCLUDE_FROM_ALL)

   add_executable(my_game src/main.cpp)
   target_link_libraries(my_game PRIVATE game_engine_lib)
   game_engine_bundle_runtime(my_game)  # copies the MinGW/SDL DLLs next to my_game.exe
   ```
3. Your `main.cpp` constructs an `Application`, builds its own `Entity`/`Sprite`
   objects for whatever the game needs, calls `app.addEntity(...)` and
   `app.setPlayer(...)`, then `app.run()` — see `src/core/main.cpp` here for
   a working example. `Application` itself has no game-specific content, so
   each game built on the engine can differ completely.
4. You'll still need SDL3/SDL3_image installed via pacman (see Build above)
   since `game_engine_lib` locates them via `find_package`.

To pick up engine changes later, update the submodule pointer:
`git -C vendored/game-engine pull origin master && git add vendored/game-engine`.

## Attribution

The sprite-loading and animation logic in `src/render/Sprite.cpp`/`Sprite.h` is used from the CSC481 boilerplate provided in class:
`M2 Class Activity/CSC481-581-M1/src/main.cpp`, lines 6-10, 34, 69-73, and 89-106. See the citation comments in `Sprite.h`/`Sprite.cpp` and `Application.cpp`.

The input and physics header files are from the CSC481 boilerplate provided in class: `M3 Class Activity/CSC481-581-M3/src`. See the citation comments in `input.h` and `physics.h`.
