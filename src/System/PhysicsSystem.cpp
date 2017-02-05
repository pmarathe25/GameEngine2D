#include "GameEngine2D/System/PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem(int expectedNumEntities) : System(expectedNumEntities) {

}

int RenderComponent::addComponent(const ComponentType& newComponent, int eID, const sf::Vector2f& position) {
    int componentIndex = System<PhysicsComponent>::addComponent(newComponent, eID);
    components[componentIndex].setPosition(position);
    return componentIndex;
}

void PhysicsSystem::update(float frametime) {
    for (std::vector<PhysicsComponent>::iterator physicsComponent = components.begin(); physicsComponent != components.end(); ++physicsComponent) {
        physicsComponent -> position += physicsComponent -> velocity * frametime;
    }
}
