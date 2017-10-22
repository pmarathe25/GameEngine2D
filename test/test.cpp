#include "ResourceManager.hpp"
#include "System/TransformSystem.hpp"
#include "System/StaticRenderSystem.hpp"
#include "Entity/EntityManager.hpp"
#include <iostream>
#include <SFML/Window.hpp>

const int WINDOW_X = 1280;
const int WINDOW_Y = 720;

int main() {
    StealthEngine::ResourceManager resourceManager;
    // Window
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "ECS Test");
    // Create Systems.
    // StealthEngine::TransformSystem transformSystem;
    // StealthEngine::StaticRenderSystem staticRenderSystem(window);
    // Entity Manager
    // StealthEngine::EntityManager entityManager(transformSystem, staticRenderSystem);
    StealthEngine::EntityManager entityManager(StealthEngine::TransformSystem{}, StealthEngine::StaticRenderSystem{window});
    // Add some components.
    for (int i = 0; i < 100; ++i) {
        entityManager.get<StealthEngine::StaticRenderSystem>().addComponent(entityManager.createEntity(), resourceManager.get<sf::Texture>("res/player.png"), {i * 10.0, i * 10.0});
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
