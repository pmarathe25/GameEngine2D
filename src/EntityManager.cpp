#include "GameEngine2D/EntityManager.hpp"

EntityManager::EntityManager(sf::RenderWindow* window, int expectedNumEntities) : renderSystem(window, expectedNumEntities) {
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
        if (newID >= entities.capacity()) {
            entities.reserve(entities.capacity() * 2);
        }
        entities.push_back(Entity(newID, position));
    }
    return newID;
}

void EntityManager::destroyEntity(int eID) {
    // Destroy all components.
    for (std::map<componentID, int>::iterator component = getEntity(eID).components.begin(); component != getEntity(eID).components.end(); ++component) {
        detachComponent(eID, component -> first);
    }
    // Push the id to the freelist.
    freeIDs.push_back(eID);
}

void EntityManager::update(float frametime) {
    renderSystem.update();
}

void EntityManager::attachComponent(int eID, const RenderComponent& component) {
    // Only attach if the component does not already exist.
    if (getEntity(eID).getComponentIndexByID(component.cID) == -1) {
        getEntity(eID).registerComponent(renderSystem.addComponent(component));
    }
}

void EntityManager::detachComponent(int eID, componentID cID) {
    // Remove it from the entity first, then from the system.
    int toRemove = getEntity(eID).deregisterComponent(cID);
    if (toRemove != -1) {
        // Detach the component from the entity and then update other entities that were modified.
        switch (cID) {
            case RENDER:
                updateEntity(renderSystem.removeComponent(toRemove), RENDER, toRemove);
                break;
        }
    }
}

Entity& EntityManager::getEntity(int eID) {
    return entities.at(eID);
}

Entity& EntityManager::getOwningEntity(const Component& component) {
    return getEntity(component.eID);
}

void EntityManager::updateEntity(int eID, componentID cID, int newComponentIndex) {
    if (eID != -1) {
        getEntity(eID).updateCommponent(cID, newComponentIndex);
    }
}
