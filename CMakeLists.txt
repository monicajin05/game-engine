cmake_minimum_required(VERSION 3.20)
project(game_engine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.h")

add_executable(game_engine ${ENGINE_SOURCES})
target_include_directories(game_engine PRIVATE src)
target_link_libraries(game_engine PRIVATE SDL3::SDL3)
