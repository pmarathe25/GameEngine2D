#include "GameEngine2D/System/PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem(int systemID, EntityManager& entityManager) : System<PhysicsComponent>(entityManager, systemID) {
}

bool PhysicsSystem::addComponent(int eID, const PhysicsComponent& newComponent) {
    bool otherEID = System<PhysicsComponent>::addComponent(eID, newComponent);
    if (otherEID) {
        componentQueue.push_back(eID);
    }
    return otherEID;
}

int PhysicsSystem::removeComponentByEntityID(int eID) {
    int otherEID = System<PhysicsComponent>::removeComponentByEntityID(eID);
    if (otherEID != -1) {
        componentQueue.push_back(eID);
        componentQueue.push_back(otherEID);
    }
    return otherEID;
}

int PhysicsSystem::removeComponentByIndex(int componentIndex, bool entityDestroyed) {
    int eID = components[componentIndex].getOwningEntityID();
    int otherEID = System<PhysicsComponent>::removeComponentByIndex(componentIndex, entityDestroyed);
    if (otherEID != -1) {
        componentQueue.push_back(eID);
        componentQueue.push_back(otherEID);
    }
    return otherEID;
}

SubscriberQueue<std::deque<int> >& PhysicsSystem::getComponentQueue() {
    return componentQueue;
}

void PhysicsSystem::update(float frametime) {
    for (std::vector<PhysicsComponent>::iterator physicsComponent = components.begin(); physicsComponent != components.end(); ++physicsComponent) {
        physicsComponent -> position += physicsComponent -> velocity * frametime;
    }
}
