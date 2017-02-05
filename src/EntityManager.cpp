#include "GameEngine2D/EntityManager.hpp"

EntityManager::EntityManager(sf::RenderWindow* window, int expectedNumEntities) : renderSystem(window, expectedNumEntities), physicsSystem(expectedNumEntities) {
    entities.reserve(expectedNumEntities);
}

int EntityManager::createEntity(const sf::Vector2f& position) {
    int newID;
    if (!freeIDs.empty()) {
        newID = freeIDs.back();
        freeIDs.pop_back();
        getEntity(newID) = Entity(newID, position);
    } else {
        newID = entities.size();
        entities.push_back(Entity(newID, position));
    }
    return newID;
}

void EntityManager::destroyEntity(int eID) {
    // Push the id to the freelist.
    freeIDs.push_back(eID);
}

bool EntityManager::attachComponent(int eID, const Component& component) {
    switch (component.getComponentID()) {
        case RENDER:
            getEntity(eID).registerComponent(RENDER, renderSystem.addComponent(static_cast<const RenderComponent&>(component), eID, getEntity(eID).position()));
            break;
        case PHYSICS:
            break;
    }
}


Entity& EntityManager::getEntity(int eID) {
    return entities[eID];
}
