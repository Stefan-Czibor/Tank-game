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

# ============ CLIENT ==============
add_executable(Tank-game
    src/main.cpp
        src/player.h
        src/player.cpp
        src/inputHandle.cpp
        src/inputHandle.h
        src/network_protokol.h
        src/network_protocol.cpp
        src/game_constants.h
)

target_link_libraries(Tank-game PRIVATE
        SFML::Graphics
        SFML::Network)

# ============= SERVER ===============
add_executable(Tank-server
        src/server_main.cpp
        src/player.h
        src/player.cpp
        src/network_protokol.h
        src/network_protocol.cpp
        src/game_constants.h
)

target_link_libraries(Tank-server PRIVATE
        SFML::Network
        SFML::System)