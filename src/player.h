//
// Created by István Czibor  on 16.09.2026.
//

#ifndef TANK_GAME_PLAYER_H
#define TANK_GAME_PLAYER_H
#include "SFML/System/Vector2.hpp"

class Player {
public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2i size;

    Player(float x, float y, float vx, float vy, int width, int height) {
        position = sf::Vector2f(x, y);
        velocity = sf::Vector2f(vx, vy);
        size = sf::Vector2i(width, height);
    }

    void update();
    void draw();
    
};

#endif //TANK_GAME_PLAYER_H
