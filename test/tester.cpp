#include "GameEngine2D/ResourceManager.hpp"
#include "GameEngine2D/Entity/EntityManager.hpp"
#include "GameEngine2D/System/RenderSystem.hpp"
#include "GameEngine2D/System/PhysicsSystem.hpp"
#include <iostream>
#include <iomanip>

const int WINDOW_X = 1280;
const int WINDOW_Y = 720;

class Benchmark {
    public:
        Benchmark() {};
        void displayRealtimePerformanceInformation() {
            std::cout << "\rCurrent Frame rate: " << std::setw(6) << framerate << " fps\tTime elapsed: " << totalFrameTime << " seconds\tNumber of Frames: " << numFrames << std::flush;
        }
        void displayAverageFramerate() {
            std::cout << "Average frame rate = " << (numFrames / totalFrameTime) << " fps" << std::endl;
        }
        void update(float frametime) {
            ++numFrames;
            totalFrameTime += frametime;
            framerate = 1 / frametime;
        }
    private:
        unsigned long long numFrames = 0;
        float totalFrameTime = 0.0;
        int framerate = 0;
};

int main() {
    ResourceManager resourceManager = ResourceManager();
    resourceManager.addResourceDirectory("test/res/");
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "ECS Test");
    EntityManager entityManager = EntityManager();
    // Create some systems.
    PhysicsSystem physicsSystem = PhysicsSystem(0, entityManager);
    RenderSystem renderSystem = RenderSystem(1, entityManager, &window, &physicsSystem);
    std::cout << "Systems created." << std::endl;
    // Register systems with the EntityManager.
    entityManager.registerSystems({&physicsSystem, &renderSystem});
    std::cout << "Systems registered." << std::endl;
    // Create clock
    sf::Clock clock;
    // Create some entities.
    for (int i = 0; i < 50000; ++i) {
        int temp = entityManager.createEntity();
        renderSystem.addComponent(temp, RenderComponent(resourceManager.getTexture("player.png")));
        physicsSystem.addComponent(temp, PhysicsComponent(sf::Vector2f(1000 * (float(rand()) / RAND_MAX - 0.5), 1000
            * (float(rand()) / RAND_MAX - 0.5)), sf::Vector2f(1000 * (float(rand()) / RAND_MAX - 0.5), 1000
            * (float(rand()) / RAND_MAX - 0.5))));
    }
    std::cout << "Components added. Time required: " << clock.getElapsedTime().asMilliseconds() << " milliseconds." << std::endl;
    // Remove some entities.
    clock.restart();
    for (int i = 49000; i >= 0; --i) {
        entityManager.destroyEntity(i);
    }
    std::cout << "Entities destroyed. Time required: " << clock.getElapsedTime().asMilliseconds() << " milliseconds." << std::endl;
    // Remove some components.
    clock.restart();
    for (int i = 49000; i >= 0; --i) {
        physicsSystem.removeComponentByEntityID(i);
    }
    std::cout << "Components removed. Time required: " << clock.getElapsedTime().asMilliseconds() << " milliseconds." << std::endl;
    // Create benchmark
    Benchmark benchmark = Benchmark();
    // Create clock for measuring frametimes.
    clock.restart();
    while (window.isOpen()) {
        // Handle events.
        sf::Event event;
        while (window.pollEvent(event)) {
          if(event.type == sf::Event::Closed) {
              window.close();
          }
        }
        float frametime = clock.restart().asSeconds();
        window.clear(sf::Color::White);
        // Benchmark.
        benchmark.update(frametime);
        benchmark.displayRealtimePerformanceInformation();
        // Systems.
        physicsSystem.update(frametime);
        renderSystem.update(frametime);
        window.display();
    }
    std::cout << std::endl;
    benchmark.displayAverageFramerate();
}
