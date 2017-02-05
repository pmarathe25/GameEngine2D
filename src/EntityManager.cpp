#include "GameEngine2D/EntityManager.hpp"

EntityManager::EntityManager(sf::RenderWindow* window, int expectedNumEntities) : renderSystem(window, expectedNumEntities), physicsSystem(expectedNumEntities) {
    entities.reserve(expectedNumEntities);
}

int EntityManager::createEntity(const sf::Vector2f& position) {
    int newID;
    if (!freeIDs.empty()) {
        newID = freeIDs.back();
        freeIDs.pop_back();
        *getEntity(newID) = Entity(newID, position);
    } else {
        newID = entities.size();
        if (newID >= entities.capacity()) {
            entities.reserve(entities.capacity() * 2);
        }
        entities.push_back(Entity(newID, position));
    }
    return newID;
}

void EntityManager::destroyEntity(int eID) {
    // Push the id to the freelist.
    freeIDs.push_back(eID);
}
