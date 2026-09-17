cmake_minimum_required(VERSION 3.10)
project(MazeVisualizer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(maze_visualizer src/main.cpp)

# --- SFML 3.x SYNTAX ---

# 1. Look specifically for SFML version 3
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# 2. Link using the new SFML:: namespace targets (capitalized)
target_link_libraries(maze_visualizer PRIVATE SFML::Graphics SFML::Window SFML::System)
