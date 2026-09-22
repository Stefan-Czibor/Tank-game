//
// Created by István Czibor  on 21.09.2026.
//

#include "inputHandle.h"
#include "SFML/Window/Keyboard.hpp"
#include "cmath"

sf::Vector2f inputHandle::getMovementDirection() {
    float vy = 0;
    float vx = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        vy = -1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        vy = 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        vx = -1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        vx = 1;

    sf::Vector2f normalisedVector;

    if (vx != 0 || vy != 0)
        normalisedVector = sf::Vector2f(vx, vy) / (sqrt(vx * vx + vy * vy));
    else
        normalisedVector = sf::Vector2f(0, 0);

    return normalisedVector;
}
