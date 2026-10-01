//
// Created by István Czibor  on 23.09.2026.
//

#include <SFML/Network.hpp>
#include <unordered_map>
#include <mutex>
#include <thread>
#include <iostream>
#include <random>
#include "network_protokol.h"
#include "player.h"

static std::unordered_map<int, Player> players;
static std::mutex playersMutex;
static int nextPlayerID = 0;
static std::mt19937 rng(std::random_device{}());

static sf::Vector2f randomSpawnPosition() {
    std::uniform_int_distribution distX(0, SCREEN_WIDTH - static_cast<int>(PLAYER_WIDTH));
    std::uniform_int_distribution distY(0, SCREEN_HEIGHT - static_cast<int>(PLAYER_HEIGHT));
    return {static_cast<float>(distX(rng)), static_cast<float>(distY(rng))};
}

static sf::Color randomColor() {
    std::uniform_int_distribution dist(50, 255);
    return sf::Color(dist(rng), dist(rng), dist(rng));
}


static int sendClientID(sf::TcpSocket* socket) {    // sends client id & returns it
    int assignedID;
    {
        std::lock_guard lock(playersMutex);     // locks the mutex until the end of this block
        assignedID = nextPlayerID;
        nextPlayerID++;


        sf::Vector2f spawnPosition = randomSpawnPosition();
        sf::Color spawnColor = randomColor();
        auto newPlayer = Player(assignedID, spawnPosition.x, spawnPosition.y, spawnColor);
        players.emplace(assignedID, newPlayer);
    }

    sf::Packet idPacket;
    idPacket << assignedID;
    sf::Socket::Status sendStatus = socket->send(idPacket);
    if (sendStatus != sf::Socket::Status::Done) {
        std::cerr << "Couln't send client id" << std::endl;
    }

    return assignedID;
}

static void updatePlayerPosition2Client(sf::Packet& getPacket, const int &playerID) {
    sf::Vector2f newPosition = deserializeOnePlayer(getPacket);

    {
        std::lock_guard lock(playersMutex);
        players[playerID].position = newPosition;
    }
}

static void sendPlayersPosition(sf::TcpSocket* socket) {
    sf::Packet sendPacket;
    {
        std::lock_guard lock(playersMutex);
        sendPacket = serializeData(players);
    }

    sf::Socket::Status sendStatus = socket->send(sendPacket);
    if (sendStatus != sf::Socket::Status::Done)
        std::cerr << "Couldn't send player position" << std::endl;
}

static void handleClient(sf::TcpSocket* socket, int playerID) {
    while (true) {
        sf::Packet getPacket;
        sf::Socket::Status recieveStatus = socket->receive(getPacket);

        if (recieveStatus == sf::Socket::Status::Disconnected || recieveStatus == sf::Socket::Status::Error) {
            {
                std::lock_guard lock(playersMutex);
                players.erase(playerID);
            }
            break;
        }

        updatePlayerPosition2Client(getPacket, playerID);
        sendPlayersPosition(socket);

    }
    delete socket;
}

int server_main() {
    sf::TcpListener listener;

    if (listener.listen(PORT) != sf::Socket::Status::Done) {
        std::cerr << "Listener couldn't be listening." << std::endl;
        return 1;
    }

    std::cout << "Server listening on port" << PORT << std::endl;

    std::vector<std::thread> clientThreads;     // threads are put here so they are kept alive
    while (true) {
        auto* socket = new sf::TcpSocket();
        if (listener.accept(*socket) == sf::Socket::Status::Done) { // if connection is successfull
            std::cout << "Connection accepted." << std::endl;

            int assignedID = sendClientID(socket);

            std::thread t(handleClient, socket, assignedID);    // new thread for the new player
            clientThreads.push_back(std::move(t));  // thread can't be copied so we have to move the whole thing

        } else {
            delete socket;  // if connection wasn't successful delete the socket
        }
    }

    return 0;
}