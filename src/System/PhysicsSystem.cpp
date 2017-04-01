#include "GameEngine2D/System/PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem(EntityManager& entityManager) : SystemType<PhysicsComponent>(entityManager) {
    systemType = 0;
}


void PhysicsSystem::update(float frametime) {
    for (std::vector<PhysicsComponent>::iterator physicsComponent = components.begin(); physicsComponent != components.end(); ++physicsComponent) {
        physicsComponent -> position += physicsComponent -> velocity * frametime;
    }
}

int PhysicsSystem::getSystemType() {
    return systemType;
}
