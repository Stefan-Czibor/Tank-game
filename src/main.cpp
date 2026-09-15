#include "SFML/Graphics.hpp"

constexpr int FPS = 60;
constexpr int SCREEN_WIDTH = 600;
constexpr int SCREEN_HEIGHT = 400;

int main() {
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Tank");
    window.setFramerateLimit(FPS);

    while (window.isOpen()) {
         while (const std::optional<sf::Event>& event = window.pollEvent()){
             if (event->is<sf::Event::Closed>())
                 window.close();

            window.clear();     // paint the display black
            window.display();   // display the actual image
        }
    }

    return 0;
}