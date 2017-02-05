#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H
#include "GameEngine2D/System/System.hpp"
#include "GameEngine2D/Component/PhysicsComponent.hpp"
#include <vector>
#include <utility>

class PhysicsSystem : public System<PhysicsComponent> {
    public:
        PhysicsSystem(int expectedNumEntities);
        int addComponent(const ComponentType& newComponent, const sf::Vector2f& position);
        void update(float frametime);
};

#endif
