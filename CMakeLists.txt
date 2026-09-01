cmake_minimum_required(VERSION 3.20)
project(game_engine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.h")

add_executable(game_engine ${ENGINE_SOURCES})
target_include_directories(game_engine PRIVATE src)
target_link_libraries(game_engine PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

# Sprites are loaded via a path relative to the working directory, so keep a
# copy of assets/ next to the built executable for ./game_engine to find.
add_custom_command(TARGET game_engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:game_engine>/assets")

# Copy the MinGW runtime and SDL DLLs next to the executable so it can be run
# directly (double-clicked, or from a shell without mingw64/bin on PATH)
# instead of only from an MSYS2 MinGW64 terminal.
get_filename_component(MINGW_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
set(RUNTIME_DLLS libgcc_s_seh-1.dll libstdc++-6.dll libwinpthread-1.dll libiconv-2.dll SDL3.dll SDL3_image.dll)
foreach(dll IN LISTS RUNTIME_DLLS)
    if(EXISTS "${MINGW_BIN_DIR}/${dll}")
        add_custom_command(TARGET game_engine POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${MINGW_BIN_DIR}/${dll}" "$<TARGET_FILE_DIR:game_engine>")
    endif()
endforeach()
