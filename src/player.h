//
// Created by István Czibor  on 16.09.2026.
//

#ifndef TANK_GAME_PLAYER_H
#define TANK_GAME_PLAYER_H
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

constexpr sf::Color PLAYER_COLOR = sf::Color::Green;

class Player {
public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f size;
    sf::RectangleShape shape;
    int playerID;

    Player(int playerID, float x, float y, float width, float height) {
        position = sf::Vector2f(x, y);
        velocity = sf::Vector2f(0, 0);
        shape.setPosition(position);
        shape.setFillColor(PLAYER_COLOR);
        shape.setSize(sf::Vector2f(width, height));
        this->playerID = playerID;
    }

    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow &window) const;

};

#endif //TANK_GAME_PLAYER_H
