#include "GameEngine2D/System/PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem(int systemID, EntityManager& entityManager) : System<PhysicsComponent>(entityManager, systemID) {
}

bool PhysicsSystem::addComponent(int eID, const PhysicsComponent& newComponent) {
    if (System<PhysicsComponent>::addComponent(eID, newComponent)) {
        componentAddedQueue.push_back(eID);
    }
}

SubscriberQueue<std::deque<int> >& PhysicsSystem::getComponentAddedQueue() {
    return componentAddedQueue;
}

void PhysicsSystem::update(float frametime) {
    for (std::vector<PhysicsComponent>::iterator physicsComponent = components.begin(); physicsComponent != components.end(); ++physicsComponent) {
        physicsComponent -> position += physicsComponent -> velocity * frametime;
    }
}
