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

## Attribution

The sprite-loading and animation logic in `src/render/Sprite.cpp`/`Sprite.h` is used from the CSC481 boilerplate provided in class:
`M2 Class Activity/CSC481-581-M1/src/main.cpp`, lines 6-10, 34, 69-73, and 89-106. See the citation comments in `Sprite.h`/`Sprite.cpp` and `Application.cpp`.
