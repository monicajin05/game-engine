cmake_minimum_required(VERSION 3.20)
project(game_engine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG)

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.h")

add_executable(game_engine ${ENGINE_SOURCES})
target_include_directories(game_engine PRIVATE src)
target_link_libraries(game_engine PRIVATE SDL3::SDL3)
