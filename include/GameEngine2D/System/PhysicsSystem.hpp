#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H
#include "GameEngine2D/System/System.hpp"
#include "GameEngine2D/Component/PhysicsComponent.hpp"
#include <vector>

class PhysicsSystem : public System {
    public:
        RenderSystem(EntityManager* entityManager, sf::RenderWindow* window, int expectedNumEntities);
        void update();
        std::pair<Component*, int> addComponent(const RenderComponent& newComponent);
        void removeComponent(int index);
    private:
        std::vector<RenderComponent> renderComponents;
        sf::RenderWindow* window;
};
