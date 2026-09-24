#include <iostream>

#include "SFML/Graphics.hpp"
#include "player.h"
#include "inputHandle.h"
#include "game_constants.h"
#include "SFML/Network/TcpSocket.hpp"
#include "SFML/Network/Packet.hpp"
#include <unordered_map>
#include <mutex>

std::unordered_map<int, Player> players;
std::mutex playersMutex;

static void updateScreen(sf::RenderWindow &window, sf::Time deltaTime, int myID) {
    std::lock_guard<std::mutex> lock(playersMutex);

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

int main() {
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Tank");
    window.setFramerateLimit(FPS);

    sf::Clock clock;

    sf::TcpSocket socket;
    int myID = -1;
    connectToServer(socket, myID);

    {
        std::lock_guard<std::mutex> lock(playersMutex);
        players.emplace(myID, Player(myID, PLAYER_X, PLAYER_Y));
    }

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