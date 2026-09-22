//
// Created by István Czibor  on 16.09.2026.
//

#include "player.h"

void Player::update(sf::Time deltaTime) {
    position += velocity * deltaTime.asSeconds();
    shape.setPosition(position);
}

void Player::draw(sf::RenderWindow &window) const {
    window.draw(shape);
}