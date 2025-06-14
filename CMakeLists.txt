cmake_minimum_required(VERSION 3.19)
project(Tanks2D LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------- SFML ----------
find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system audio)

# ---------- библиотека игры ----------
file(GLOB GAME_SRC src/*.cpp src/*.hpp)
add_library(game_objects STATIC ${GAME_SRC})
target_link_libraries(game_objects PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

# ---------- само приложение ----------
add_executable(tanks2d src/main.cpp)          # если main.cpp у тебя в src/
target_link_libraries(tanks2d PRIVATE game_objects)

# ---------- Catch2 single-header ----------
enable_testing()

add_executable(tests
    external/Catch2/catch_amalgamated.cpp
    tests/tests.cpp)
target_include_directories(tests PRIVATE
    external/Catch2             # для .cpp
    external/Catch2/include     # для .hpp
    src)
target_link_libraries(tests PRIVATE game_objects)

add_test(NAME all_tests COMMAND tests)