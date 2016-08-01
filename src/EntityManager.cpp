#include "GameEngine2D/EntityManager.hpp"

EntityManager::EntityManager(sf::RenderWindow* window, int expectedNumEntities) : renderSystem(this, window, expectedNumEntities) {
    entities.reserve(expectedNumEntities);
}

int EntityManager::createEntity(const sf::Vector2f& position) {
    int newID;
    if (!freeIDs.empty()) {
        newID = freeIDs.back();
        freeIDs.pop_back();
        entities.at(newID) = Entity(newID, position);
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
    // Destroy all components.
    for (std::map<componentID, int>::iterator component = entities.at(eID).components.begin(); component != entities.at(eID).components.end(); ++component) {
        switch (component -> first) {
            case RENDER:
                renderSystem.removeComponent(component -> second);
        }
    }
    // Push the id to the freelist.
    freeIDs.push_back(eID);
}

void EntityManager::update(float frametime) {
    renderSystem.update();
}

void EntityManager::attachComponent(int eID, const RenderComponent& component) {
    // Only attach if the component does not already exist.
    if (entities.at(eID).getComponentIndexByID(component.cID) == -1) {
        entities.at(eID).registerComponent(renderSystem.addComponent(component));
    }
}

void EntityManager::detachComponent(int eID, componentID cID) {
    // Remove it from the entity first, then from the system.
    int toRemove = entities.at(eID).deregisterComponent(cID);
    if (toRemove != -1) {
        switch (cID) {
            case RENDER:
                renderSystem.removeComponent(toRemove);
        }
    }
}

Entity& EntityManager::getEntity(int eID) {
    return entities.at(eID);
}

Entity& EntityManager::getOwningEntity(const Component& component) {
    return entities.at(component.eID);
}
