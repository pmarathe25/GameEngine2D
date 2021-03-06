#include "GameEngine2D/ResourceManager.hpp"
#include "GameEngine2D/EntityManager.hpp"
#include <iostream>

const int WINDOW_X = 1280;
const int WINDOW_Y = 720;

int main() {
    ResourceManager resourceManager = ResourceManager();
    resourceManager.addResourceDirectory("res/");
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "ECS Test");
    EntityManager entityManager = EntityManager(&window, 100);
    for (int i = 1; i < 10000; ++i) {
        int temp = entityManager.createEntity(sf::Vector2f(WINDOW_X * float(rand()) / RAND_MAX, WINDOW_Y * float(rand()) / RAND_MAX));
        entityManager.attachComponent(temp, RenderComponent(resourceManager.getTexture("player.png")));
        entityManager.attachComponent(temp, PhysicsComponent(sf::Vector2f(100 * (float(rand()) / RAND_MAX - 0.5), 100 * (float(rand()) / RAND_MAX - 0.5))));
    }
    // Remove some entities.
    for (int i = 1; i < 3; ++i) {
        entityManager.destroyEntity(i);
    }
    // Remove some components.
    for (int i = 3; i < 10; ++i) {
        entityManager.detachComponent(i, RENDER);
    }
    sf::Clock clock;
    while (window.isOpen()) {
        // Handle events.
        sf::Event event;
        while (window.pollEvent(event)) {
          if(event.type == sf::Event::Closed) {
              window.close();
          }
        }
        float frametime = clock.restart().asSeconds();
        std::cout << (1 / frametime) << std::endl;
        window.clear(sf::Color::White);
        entityManager.update(frametime);
        window.display();
    }
}
