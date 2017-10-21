#include "ResourceManager.hpp"
#include "System/TransformSystem.hpp"
#include <iostream>
#include <SFML/Window.hpp>

const int WINDOW_X = 1280;
const int WINDOW_Y = 720;

int main() {
    StealthEngine::ResourceManager resourceManager;
    const sf::Texture& player = resourceManager.get<sf::Texture>("res/player.png");
    // std::cout << resourceManager.remove("res/player.png") << std::endl;

    // Create Systems.
    StealthEngine::TransformSystem transformSystem;

    sf::Sprite sprite;
    sprite.setTexture(player);

    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "ECS Test");

    while (window.isOpen()) {
        // Handle events.
        sf::Event event;
        while (window.pollEvent(event)) {
          if(event.type == sf::Event::Closed) {
              window.close();
          }
        }
        window.clear(sf::Color::White);
        window.draw(sprite);
        window.display();
    }


}
