#include "SFML/Graphics.hpp"
#include "player.h"
#include "inputHandle.h"
#include "iostream"

//============== GAME WINDOW ============
constexpr int FPS = 60;
constexpr int SCREEN_WIDTH = 600;
constexpr int SCREEN_HEIGHT = 400;

//============== PLAYER =================
constexpr float PLAYER_X = 30;
constexpr float PLAYER_Y = 30;
constexpr float PLAYER_SPEED = 100;
constexpr float PLAYER_WIDTH = 40;
constexpr float PLAYER_HEIGHT = 40;

void updateScreen(Player &player, const sf::Time &deltaTime, sf::RenderWindow &window) {
    sf::Vector2f direction = inputHandle::getMovementDirection();
    direction = direction * PLAYER_SPEED;   // direction vector with real length
    player.velocity = direction;

    player.update(deltaTime);
    player.draw(window);
}

int main() {
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Tank");
    window.setFramerateLimit(FPS);

    Player player(PLAYER_X, PLAYER_Y, PLAYER_WIDTH, PLAYER_HEIGHT);
    sf::Clock clock;

    while (window.isOpen()) {

        sf::Time deltaTime = clock.restart();

         while (const std::optional<sf::Event>& event = window.pollEvent()) {
             if (event->is<sf::Event::Closed>())
                 window.close();
            }

        window.clear();     // paint the display black
        updateScreen(player, deltaTime, window);
        window.display();   // display the actual image

    }

    return 0;
}