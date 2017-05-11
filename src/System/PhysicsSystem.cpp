#include "GameEngine2D/System/PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem(int systemID, EntityManager& entityManager) : System<PhysicsComponent>(entityManager, systemID) {
}

bool PhysicsSystem::addComponent(int eID, const PhysicsComponent& newComponent) {
    bool temp = System<PhysicsComponent>::addComponent(eID, newComponent);
    if (temp) {
        componentQueue.push_back(eID);
    }
    return temp;
}

bool PhysicsSystem::removeComponentByEntityID(int eID) {
    bool temp = System<PhysicsComponent>::removeComponentByEntityID(eID);
    if (temp) {
        componentQueue.push_back(eID);
    }
    return temp;
}

int PhysicsSystem::removeComponentByIndex(int componentIndex, bool entityDestroyed) {
    int eID = System<PhysicsComponent>::removeComponentByIndex(componentIndex, entityDestroyed);
    if (eID != -1) {
        componentQueue.push_back(eID);
    }
    return eID;
}

SubscriberQueue<std::deque<int> >& PhysicsSystem::getComponentQueue() {
    return componentQueue;
}

void PhysicsSystem::update(float frametime) {
    for (std::vector<PhysicsComponent>::iterator physicsComponent = components.begin(); physicsComponent != components.end(); ++physicsComponent) {
        physicsComponent -> position += physicsComponent -> velocity * frametime;
    }
}
