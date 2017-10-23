#include "ResourceManager.hpp"
#include "System/TransformSystem.hpp"
#include "System/Render/StaticRenderSystem.hpp"
#include "System/Render/DynamicRenderSystem.hpp"
#include "System/Movement/TopDownPlayerMovementSystem.hpp"
#include "Entity/EntityManager.hpp"
#include "Entity/EntityFactory.hpp"
#include <SFML/Window.hpp>
#include <iostream>
#include <iomanip>
#include <limits>

const int WINDOW_X = 1600;
const int WINDOW_Y = 900;

class Benchmark {
    public:
        Benchmark() {};
        void displayRealtimePerformanceInformation() {
            std::cout << "\rCurrent Framerate: " << std::setw(4) << framerate << " fps\tTime elapsed: " << std::setw(8) << totalFrameTime << " seconds\tNumber of Frames: " << numFrames << std::flush;
        }
        void displayFramerateInformation() {
            std::cout << "Minimum Framerate: " << minFramerate << " fps\tAverage Framerate: " << (numFrames / totalFrameTime) << " fps\tMaximium Framerate: " << maxFramerate << " fps" << std::endl;
        }
        void update(float frametime) {
            ++numFrames;
            totalFrameTime += frametime;
            if (frametime != 0) {
                framerate = 1 / frametime;
                if  (framerate < minFramerate) {
                    minFramerate = framerate;
                } else if (framerate > maxFramerate) {
                    maxFramerate = framerate;
                }
            }
        }
    private:
        unsigned long long numFrames = 0;
        float totalFrameTime = 0.0;
        int framerate = 0, minFramerate = std::numeric_limits<int>::max(), maxFramerate = -1;
} benchmark;

const std::map<StealthEngine::Intent, sf::Keyboard::Key> keymap{
    {StealthEngine::MOVE_UP, sf::Keyboard::W},
    {StealthEngine::MOVE_DOWN, sf::Keyboard::S},
    {StealthEngine::MOVE_LEFT, sf::Keyboard::A},
    {StealthEngine::MOVE_RIGHT, sf::Keyboard::D},
};

int main() {
    StealthEngine::ResourceManager resourceManager;
    // Window
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "ECS Test");
    // Systems
    StealthEngine::TransformSystem transformSystem{};
    StealthEngine::StaticRenderSystem staticRenderSystem{window};
    StealthEngine::DynamicRenderSystem dynamicRenderSystem{window, transformSystem};
    StealthEngine::TopDownPlayerMovementSystem playerMovementSystem{keymap, transformSystem};
    // Entity Manager
    StealthEngine::EntityManager entityManager(transformSystem, staticRenderSystem, dynamicRenderSystem, playerMovementSystem);
    // Entity Factory
    StealthEngine::EntityFactory entityFactory(entityManager, resourceManager);
    // Create a group of "player" entities in the entityManager.
    StealthEngine::EntityGroup players = entityFactory.createEntityGroup<StealthEngine::PLAYER>(10000);
    for (auto& player : players) {
        entityManager.get<StealthEngine::TransformSystem>().position(player) = {player * 10, player * 10};
    }
    // Remove all the entities!
    // entityFactory.destroyEntityGroup(players);
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
        // Benchmark.
        benchmark.update(frametime);
        benchmark.displayRealtimePerformanceInformation();
    }
    std::cout << std::endl;
    benchmark.displayFramerateInformation();
}
