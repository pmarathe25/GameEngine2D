#include "ResourceManager.hpp"
#include "System/TransformSystem.hpp"
#include "System/StaticRenderSystem.hpp"
#include "System/DynamicRenderSystem.hpp"
#include "Entity/EntityManager.hpp"
#include "Entity/EntityFactory.hpp"
#include <SFML/Window.hpp>
#include <iostream>

const int WINDOW_X = 1280;
const int WINDOW_Y = 720;

int main() {
    StealthEngine::ResourceManager resourceManager;
    // Window
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "ECS Test");
    // Systems
    StealthEngine::TransformSystem transformSystem{};
    StealthEngine::StaticRenderSystem staticRenderSystem{window};
    StealthEngine::DynamicRenderSystem dynamicRenderSystem{window, transformSystem};
    // Entity Manager
    StealthEngine::EntityManager entityManager(transformSystem, staticRenderSystem, dynamicRenderSystem);
    // Entity Factory
    StealthEngine::EntityFactory entityFactory(entityManager, resourceManager);
    // Create a group of "player" entities in the entityManager.
    StealthEngine::EntityGroup players = entityFactory.createEntityGroup<StealthEngine::PLAYER>(100);
    for (auto& player : players) {
        entityManager.get<StealthEngine::TransformSystem>().position(player) = {50, 50};
    }
    // Remove all the entities!
    // for (int i = 0; i < 100; ++i) {
    //     entityManager.destroyEntity(i);
    // }
    // Main Loop.
    sf::Clock clock;
    while (window.isOpen()) {
        // Handle events.
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
              window.close();
            }
        }
        // Calculate frametime
        float frametime = clock.restart().asSeconds();
        // Clear previous frame.
        window.clear(sf::Color::White);
        // Update all systems
        entityManager.update(frametime);
        // Display.
        window.display();
    }


}
