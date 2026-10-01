#include <iostream>

#include "SFML/Graphics.hpp"
#include "player.h"
#include "inputHandle.h"
#include "game_constants.h"
#include "SFML/Network/TcpSocket.hpp"
#include "SFML/Network/Packet.hpp"
#include "network_protokol.h"
#include <unordered_map>
#include <mutex>
#include <functional>
#include <thread>

std::unordered_map<int, Player> players;
std::mutex playersMutex;

static void updateScreen(sf::RenderWindow &window, sf::Time deltaTime, int myID) {
    std::lock_guard lock(playersMutex);

    sf::Vector2f direction = inputHandle::getMovementDirection();
    direction = direction * PLAYER_SPEED;   // direction vector with real length
    players[myID].velocity = direction;

    for ( auto& [id, player]: players) {
        player.update(deltaTime);
        player.draw(window);
    }
}

static void connectToServer(sf::TcpSocket &socket, int &myID) {
    if (socket.connect(IP, PORT) != sf::Socket::Status::Done) {
        std::cerr << "Could not connect to server!" << std::endl;
        return;
    }

    sf::Packet packet;
    sf::Socket::Status status = socket.receive(packet);

    if (status != sf::Socket::Status::Done) {
        std::cerr << "Could not connect to server!" << std::endl;
        return;
    }
    packet >> myID;
}

static void sendDataToServer(sf::TcpSocket &socket, int &myID) {
    sf::Packet sendPacket;
    {
        std::lock_guard lock(playersMutex);
        sendPacket = serializeOnePlayer(players[myID].position);
    }

    sf::Socket::Status sendStatus = socket.send(sendPacket);
    if (sendStatus != sf::Socket::Status::Done) {
        std::cerr << "Could not send data to server!" << std::endl;
        return;
    }
}

static void recieveDataFromServer(sf::TcpSocket &socket) {
    sf::Packet recievePacket;
    sf::Socket::Status recieveStatus = socket.receive(recievePacket);
    if (recieveStatus != sf::Socket::Status::Done) {
        std::cerr << "Could not receive data from server!" << std::endl;
        return;
    }
    {
        std::lock_guard lock(playersMutex);
        players = deserializeData(recievePacket);
    }
}

static void networkLoop(sf::TcpSocket &socket, int &myID) {
    while (true) {          // while there is connection
        sendDataToServer(socket, myID);
        recieveDataFromServer(socket);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Tank");
    window.setFramerateLimit(FPS);

    sf::Clock clock;

    sf::TcpSocket socket;
    int myID = -1;
    connectToServer(socket, myID);

    {
        std::lock_guard lock(playersMutex);
        players.emplace(myID, Player(myID, myID * 50, myID * 50));
    }

    std::thread networkThread(networkLoop, std::ref(socket), std::ref(myID));

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();

         while (const std::optional<sf::Event>& event = window.pollEvent()) {
             if (event->is<sf::Event::Closed>())
                 window.close();
            }

        window.clear();     // paint the display black
        updateScreen(window, deltaTime, myID);
        window.display();   // display the actual image

    }

    return 0;
}