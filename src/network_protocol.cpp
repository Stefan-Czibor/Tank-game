//
// Created by István Czibor  on 23.09.2026.
//

#include <SFML/Network.hpp>
#include "player.h"


// ======================== Server -> client ==============================

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
    std::unordered_map<int, Player> players;
    int playerCount;
    packet >> playerCount;

    int playerID;
    float playerX, playerY;
    for (int i = 0; i < playerCount; i++) {
        packet >> playerID >> playerX >> playerY;
        players.emplace(playerID, Player(playerID, playerX, playerY));
    }

    return players;
}

// ======================== Client -> server ==============================

sf::Packet serializeOnePlayer(const sf::Vector2f& position) {
    sf::Packet packet;
    packet << position.x << position.y;
    return packet;
}

sf::Vector2f deserializeOnePlayer(sf::Packet& packet) {
    float x, y;
    packet >> x >> y;
    return {x, y};
}