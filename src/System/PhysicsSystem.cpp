#include "GameEngine2D/System/PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem(int systemID, EntityManager& entityManager) : System<PhysicsComponent>(entityManager, systemID) {
}

void PhysicsSystem::update(float frametime) {
    for (std::vector<PhysicsComponent>::iterator physicsComponent = components.begin(); physicsComponent != components.end(); ++physicsComponent) {
        physicsComponent -> position += physicsComponent -> velocity * frametime;
    }
}
