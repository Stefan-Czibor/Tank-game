#include "SFML/Graphics.hpp"
#include "player.h"

//============== GAME WINDOW ============
constexpr int FPS = 60;
constexpr int SCREEN_WIDTH = 600;
constexpr int SCREEN_HEIGHT = 400;

//============== PLAYER =================
constexpr float PLAYER_X = 30;
constexpr float PLAYER_Y = 30;
constexpr float PLAYER_SPEED_X = 3;
constexpr float PLAYER_SPEED_Y = 3;
constexpr float PLAYER_WIDTH = 40;
constexpr float PLAYER_HEIGHT = 40;

int main() {
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Tank");
    window.setFramerateLimit(FPS);

    Player player(PLAYER_X, PLAYER_SPEED_Y, PLAYER_SPEED_X, PLAYER_SPEED_Y, PLAYER_WIDTH, PLAYER_HEIGHT);
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