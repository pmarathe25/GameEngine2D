#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H
#include "GameEngine2D/System/SystemType.hpp"
#include "GameEngine2D/System/PhysicsSystem.hpp"
#include "GameEngine2D/Component/RenderComponent.hpp"
#include <vector>
#include <SFML/Window.hpp>

class RenderSystem : public SystemType<RenderComponent> {
    public:
        RenderSystem(int systemID, EntityManager& entityManager, sf::RenderWindow* window, PhysicsSystem* physicsSystem = 0);
        void update(float frametime);
    private:
        bool isOffScreen(const sf::Vector2f& position, const sf::Vector2u& size);
        sf::RenderWindow* window;
        PhysicsSystem* physicsSystem;
};

#endif
