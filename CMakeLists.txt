cmake_minimum_required(VERSION 3.20)

project(Tank-game)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
)

FetchContent_MakeAvailable(SFML)

add_executable(Tank-game
    src/main.cpp
        src/player.h
        src/player.cpp
        src/inputHandle.cpp
        src/inputHandle.h
)

target_link_libraries(Tank-game PRIVATE SFML::Graphics)