//
// Created by István Czibor  on 23.09.2026.
//

#include <SFML/Network.hpp>
#include "player.h"

sf::Packet serializeData(const std::unordered_map<int, Player> &players) {
    sf::Packet packet;
    int playerCount = static_cast<int>(players.size());
    packet << playerCount;
    for (const auto& [id, player] : players) {
        packet << id << player.position.x << player.position.y;
    }

    return packet;
}

std::unordered_map<int, Player> deserializeData(sf::Packet &packet) {
    
}