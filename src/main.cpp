#include "SFML/Graphics.hpp"
#include "player.h"

constexpr int FPS = 60;
constexpr int SCREEN_WIDTH = 600;
constexpr int SCREEN_HEIGHT = 400;

int main() {
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Tank");
    window.setFramerateLimit(FPS);

    Player player(30, 30, 3, 3, 40, 40);
    sf::Clock clock;

    while (window.isOpen()) {

        sf::Time deltaTime = clock.restart();

         while (const std::optional<sf::Event>& event = window.pollEvent()){
             if (event->is<sf::Event::Closed>())
                 window.close();

             player.update(deltaTime);
            window.clear();     // paint the display black
             player.draw(window);
            window.display();   // display the actual image
        }
    }

    return 0;
}