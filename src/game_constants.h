//
// Created by István Czibor  on 23.09.2026.
//

#ifndef TANK_GAME_GAME_CONSTANS_H
#define TANK_GAME_GAME_CONSTANS_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Network/IpAddress.hpp>

//============== GAME WINDOW ============
constexpr int FPS = 60;
constexpr int SCREEN_WIDTH = 600;
constexpr int SCREEN_HEIGHT = 400;

//============== PLAYER =================
constexpr float PLAYER_X = 30;
constexpr float PLAYER_Y = 30;
constexpr float PLAYER_SPEED = 100;
constexpr float PLAYER_WIDTH = 40;
constexpr float PLAYER_HEIGHT = 40;
constexpr sf::Color PLAYER_COLOR = sf::Color::Green;

// =============== NETWORK ==============
constexpr int PORT = 2000;  // specific ports are 0-1023 everything above is free
inline const sf::IpAddress IP = sf::IpAddress::LocalHost;

#endif //TANK_GAME_GAME_CONSTANTS_H
