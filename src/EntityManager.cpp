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
    // Destroy all components.
    for (std::map<componentID, int>::iterator component = getEntity(eID) -> components.begin(); component != getEntity(eID) -> components.end(); ++component) {
        detachComponent(eID, component -> first);
    }
    // Push the id to the freelist.
    freeIDs.push_back(eID);
}

void EntityManager::update(float frametime) {
    renderSystem.update();
    physicsSystem.update(frametime);
    sync();
}

bool EntityManager::attachComponent(int eID, const Component& component) {
    // Only attach if the component does not already exist.
    if (getEntity(eID) -> getComponentIndexByID(component.cID) != -1) {
        return false;
    }
    // Cast based on what kind of component it is.
    switch (component.cID) {
        case RENDER:
            getEntity(eID) -> registerComponent(renderSystem.addComponent(static_cast<const RenderComponent&>(component)));
            break;
        case PHYSICS:
            getEntity(eID) -> registerComponent(physicsSystem.addComponent(static_cast<const PhysicsComponent&>(component)));
            break;
    }
    return true;
}

bool EntityManager::detachComponent(int eID, componentID cID) {
    // Remove it from the entity first, then from the system.
    int toRemove = getEntity(eID) -> deregisterComponent(cID);
    // If the entity does not have the component.
    if (toRemove == -1) {
        return false;
    }
    // Detach the component from the entity and then update other entities that were modified.
    switch (cID) {
        case RENDER:
            updateEntity(renderSystem.removeComponent(toRemove), RENDER, toRemove);
            break;
        case PHYSICS:
            updateEntity(physicsSystem.removeComponent(toRemove), PHYSICS, toRemove);
            break;
    }
    return true;
}

Entity* EntityManager::getEntity(int eID) {
    return &entities.at(eID);
}

Entity* EntityManager::getOwningEntity(const Component& component) {
    return getEntity(component.eID);
}

Entity* EntityManager::getOwningEntity(const Component* component) {
    return getEntity(component -> eID);
}

void EntityManager::updateEntity(int eID, componentID cID, int componentIndex) {
    if (eID != -1) {
        getEntity(eID) -> updateCommponent(cID, componentIndex);
    }
}

void EntityManager::sync() {
    PhysicsComponent* nextPhysicsComponent;
    Entity* entityToSync;
    int renderComponentIndex;
    // Sync physics and render systems.
    while (physicsSystem.hasNext()) {
        nextPhysicsComponent = physicsSystem.next();
        entityToSync = getOwningEntity(nextPhysicsComponent);
        renderComponentIndex = entityToSync -> getComponentIndexByID(RENDER);
        if (renderComponentIndex != -1) {
            entityToSync -> position = nextPhysicsComponent -> position;
            renderSystem.getComponentByIndex(renderComponentIndex) -> sprite.setPosition(nextPhysicsComponent -> position);
        }
    }
}
