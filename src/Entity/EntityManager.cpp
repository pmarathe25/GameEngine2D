#include "GameEngine2D/Entity/EntityManager.hpp"
#include "GameEngine2D/System/System.hpp"

EntityManager::EntityManager() {

}

int EntityManager::createEntity() {
    int newID;
    if (!freeIDs.empty()) {
        newID = freeIDs.back();
        freeIDs.pop_back();
        entities[newID].activate();
    } else {
        newID = entities.size();
        entities.push_back(Entity());
    }
    return newID;
}

void EntityManager::destroyEntity(int eID) {
    // Remove all of this entity's components.
    for (std::map<int, int>::iterator componentTuple = entities[eID].getComponentMap().begin(); componentTuple != entities[eID].getComponentMap().end(); ++componentTuple) {
        systems[componentTuple -> first] -> removeComponentByIndex(componentTuple -> second, true);
    }
    // Push it to the free IDs deque.
    freeIDs.push_back(eID);
    entities[eID].deactivate();
}

void EntityManager::registerSystems(std::vector<SystemParent*> unregisteredSystems) {
    for (std::vector<SystemParent*>::iterator sys = unregisteredSystems.begin(); sys != unregisteredSystems.end(); ++sys) {
        systems[(*sys) -> getSystemID()] = *sys;
    }
}

Entity* EntityManager::getEntity(int eID) {
    Entity* entity = &entities[eID];
    return (entity -> isActive()) ? entity : NULL;
}

Entity* EntityManager::getEntity(const Component& component) {
    return getEntity(component.getOwningEntityID());
}

Entity* EntityManager::getEntity(const Component* component) {
    return getEntity(component -> getOwningEntityID());
}

int EntityManager::size() {
    return entities.size();
}
