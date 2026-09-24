//
// Created by István Czibor  on 23.09.2026.
//

#ifndef TANK_GAME_NETWORK_PROTOKOL_H
#define TANK_GAME_NETWORK_PROTOKOL_H

#include <SFML/Network.hpp>
#include "player.h"


// Server -> client communication protocol
sf::Packet serializeData(const std::unordered_map<int, Player> &players);
std::unordered_map<int, Player> deserializeData(sf::Packet &packet);

// Client -> server communication protocol
sf::Packet serializeOnePlayer(sf::Vector2f& position);
sf::Vector2f deserializeOnePlayer(sf::Packet& packet);


#endif //TANK_GAME_NETWORK_PROTOKOL_H
