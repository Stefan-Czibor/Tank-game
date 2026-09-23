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

}

int server_main() {
    sf::TcpListener listener;

    if (listener.listen(PORT) != sf::Socket::Status::Done) {
        std::cerr << "Listener couldn't be listening." << std::endl;
        return 1;
    }

    std::cout << "Server listening on port" << PORT << std::endl;

    std::vector<std::thread> clientThreads;



    return 0;
}