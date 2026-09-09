cmake_minimum_required(VERSION 3.20)
project(game_engine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)

# Engine library: everything needed to build a game on top of this engine.
# Other repos consume this by adding it as a subdirectory (e.g. via a git
# submodule) and linking against the `game_engine_lib` target.
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.h")
list(REMOVE_ITEM ENGINE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/core/main.cpp")

add_library(game_engine_lib STATIC ${ENGINE_SOURCES})
target_include_directories(game_engine_lib PUBLIC src)
target_link_libraries(game_engine_lib
    PUBLIC SDL3::SDL3
    PRIVATE SDL3_image::SDL3_image)

# Copies the MinGW runtime and SDL DLLs next to a built executable so it can
# be run directly (double-clicked, or from a shell without mingw64/bin on
# PATH) instead of only from an MSYS2 MinGW64 terminal. Any project linking
# against game_engine_lib -- including one that pulled this repo in as a
# submodule -- can call this for its own executable target.
function(game_engine_bundle_runtime target)
    get_filename_component(mingw_bin_dir "${CMAKE_CXX_COMPILER}" DIRECTORY)
    set(runtime_dlls libgcc_s_seh-1.dll libstdc++-6.dll libwinpthread-1.dll
        libiconv-2.dll SDL3.dll SDL3_image.dll)
    foreach(dll IN LISTS runtime_dlls)
        if(EXISTS "${mingw_bin_dir}/${dll}")
            add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${mingw_bin_dir}/${dll}" "$<TARGET_FILE_DIR:${target}>")
        endif()
    endforeach()
endfunction()

# Demo executable showcasing the engine's capabilities.
add_executable(game_engine src/core/main.cpp)
target_link_libraries(game_engine PRIVATE game_engine_lib)

# Sprites are loaded via a path relative to the working directory, so keep a
# copy of assets/ next to the built executable for ./game_engine to find.
add_custom_command(TARGET game_engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:game_engine>/assets")

game_engine_bundle_runtime(game_engine)
