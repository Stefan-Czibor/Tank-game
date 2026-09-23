#include "SFML/Graphics.hpp"
#include "player.h"
#include "inputHandle.h"
#include "game_constans.h"

static void updateScreen(Player &player, const sf::Time &deltaTime, sf::RenderWindow &window) {
    sf::Vector2f direction = inputHandle::getMovementDirection();
    direction = direction * PLAYER_SPEED;   // direction vector with real length
    player.velocity = direction;

    player.update(deltaTime);
    player.draw(window);
}

int main() {
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Tank");
    window.setFramerateLimit(FPS);

    Player player(0, PLAYER_X, PLAYER_Y);
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