#include "GameEngine2D/ResourceManager.hpp"
#include "GameEngine2D/Entity/EntityManager.hpp"
#include "GameEngine2D/System/RenderSystem.hpp"
#include "GameEngine2D/System/PhysicsSystem.hpp"
#include <iostream>

const int WINDOW_X = 1280;
const int WINDOW_Y = 720;

int main() {
    ResourceManager resourceManager = ResourceManager();
    resourceManager.addResourceDirectory("test/res/");
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "ECS Test");
    EntityManager entityManager = EntityManager();
    PhysicsSystem physicsSystem = PhysicsSystem(0, entityManager);
    RenderSystem renderSystem = RenderSystem(1, entityManager, &window, &physicsSystem);
    for (int i = 0; i < 50000; ++i) {
        int temp = entityManager.createEntity();
        renderSystem.addComponent(temp, RenderComponent(resourceManager.getTexture("player.png")));
    }
    for (int i = 0; i < 49000; ++i) {
        physicsSystem.addComponent(i, PhysicsComponent(sf::Vector2f(1000 * (float(rand()) / RAND_MAX - 0.5), 1000
        * (float(rand()) / RAND_MAX - 0.5)), sf::Vector2f(1000 * (float(rand()) / RAND_MAX - 0.5), 1000
        * (float(rand()) / RAND_MAX - 0.5))));
    }
    // Remove some entities.
    // for (int i = 1; i < 3; ++i) {
    //     entityManager.destroyEntity(i);
    // }
    // // Remove some components.
    // for (int i = 3; i < 10; ++i) {
    //     entityManager.detachComponent(i, RENDER);
    // }
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
        physicsSystem.update(frametime);
        renderSystem.update(frametime);
        window.display();
    }
}
