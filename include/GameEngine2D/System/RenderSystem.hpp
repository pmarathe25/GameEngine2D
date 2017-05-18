#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H
#include "GameEngine2D/System/System.hpp"
#include "GameEngine2D/System/PhysicsSystem.hpp"
#include "GameEngine2D/Component/RenderComponent.hpp"
#include <SFML/Window.hpp>

class RenderSystem : public System<RenderComponent> {
    public:
        RenderSystem(int systemID, EntityManager& entityManager, sf::RenderWindow* window, PhysicsSystem* physicsSystem = NULL);
        bool addComponent(int eID, const RenderComponent& newComponent);
        void update(float frametime);
    private:
        bool isOffScreen(const sf::Vector2f& position, const sf::Vector2u& size);
        sf::RenderWindow* window;
        PhysicsSystem* physicsSystem;
};

#endif
