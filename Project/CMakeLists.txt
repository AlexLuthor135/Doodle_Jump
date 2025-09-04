cmake_minimum_required(VERSION 3.16)
project(Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)

add_executable(Project 
    game.cpp
    src/GameEngine.cpp
    src/GameManager.cpp
    src/BulletManager.cpp
    src/EnemyManager.cpp
    src/AbilityManager.cpp
    src/PlatformManager.cpp
    src/CollisionManager.cpp
)

target_link_libraries(Project
    PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
)