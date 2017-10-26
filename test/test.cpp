#include "ResourceManager.hpp"
#include "World.hpp"
#include "EventManager.hpp"
#include "System/SystemManager.hpp"
#include "System/Render/StaticRenderSystem.hpp"
#include "System/Render/DynamicRenderSystem.hpp"
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

// const std::map<StealthEngine::Intent, sf::Keyboard::Key> keymap{
//     {StealthEngine::MOVE_UP, sf::Keyboard::W},
//     {StealthEngine::MOVE_DOWN, sf::Keyboard::S},
//     {StealthEngine::MOVE_LEFT, sf::Keyboard::A},
//     {StealthEngine::MOVE_RIGHT, sf::Keyboard::D},
// };

int main() {
    // World, event and resource manager.
    StealthEngine::EventManager eventManager;
    StealthEngine::World world{eventManager};
    StealthEngine::ResourceManager resourceManager;
    // Window
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "ECS Test");
    // Systems
    StealthEngine::StaticRenderSystem staticRenderSystem{world, eventManager, window};
    StealthEngine::DynamicRenderSystem dynamicRenderSystem{world, eventManager, window};
    // System Manager
    StealthEngine::SystemManager systemManager{staticRenderSystem, dynamicRenderSystem};
    // Entity Factory
    StealthEngine::EntityFactory entityFactory(world, systemManager, resourceManager);
    // Create a group of "player" entities in the entityManager.
    StealthEngine::EntityGroup players = entityFactory.createEntityGroup<StealthEngine::PLAYER>(150000);


    for (auto& player : players) {
        world.setPosition(player, {10, 10});
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
        systemManager.update(frametime);
        // Display.
        window.display();
        // Benchmark.
        benchmark.update(frametime);
        benchmark.displayRealtimePerformanceInformation();
    }
    std::cout << std::endl;
    benchmark.displayFramerateInformation();
}
