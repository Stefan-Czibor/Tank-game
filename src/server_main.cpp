//
// Created by István Czibor  on 23.09.2026.
//

#include <SFML/Network.hpp>
#include <unordered_map>
#include <mutex>
#include <thread>
#include <iostream>
#include "player.h"

constexpr int PORT = 2000;  // specific ports are 0-1023 everything above is free

std::unordered_map<int, Player> players;
std::mutex playersMutex;
int nextPlayerID = 0;


void handleClient(sf::TcpSocket* socket, int playerID) {
    sf::Packet packet;
    // packet << playerID << x << y;
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

            int assignedID;
            {
                std::lock_guard lock(playersMutex);     // locks the mutex until the end of this block
                assignedID = nextPlayerID;
                nextPlayerID++;

                auto newPlayer = Player(assignedID, 40, 40);
                players.emplace(assignedID, newPlayer);
            }

            std::thread t(handleClient, socket, assignedID);    // new thread for the new player
            clientThreads.push_back(std::move(t));  // thread can't be copied so we have to move the whole thing

        } else {
            delete socket;  // if connection wasn't successful delete the socket
        }
    }

    return 0;
}