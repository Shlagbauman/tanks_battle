cmake_minimum_required(VERSION 3.10)
project(TankDuel)

set(CMAKE_CXX_STANDARD 17)

# Ищем SFML (нужна установлена SFML >= 2.5)
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

add_executable(TankDuel
    src/main.cpp
    src/Game.cpp
    src/Map.cpp
    src/Entity.cpp
    src/Tank.cpp
    src/Bullet.cpp
    src/Input.cpp
)

target_include_directories(TankDuel PRIVATE include)
target_link_libraries(TankDuel sfml-system sfml-window sfml-graphics sfml-audio)