#include "GameEngine2D/EntityManager.hpp"

EntityManager::EntityManager() {

}

int EntityManager::createEntity() {
    int newID;
    if (!freeIDs.empty()) {
        newID = freeIDs.back();
        freeIDs.pop_back();
        getEntity(newID) = Entity();
    } else {
        newID = entities.size();
        entities.push_back(Entity());
    }
    return newID;
}

void EntityManager::destroyEntity(int eID) {
    // Push the id to the freelist.
    freeIDs.push_back(eID);
    // TODO: Detach all components.
}

Entity& EntityManager::getEntity(int eID) {
    return entities[eID];
}

Entity& EntityManager::getEntity(const Component& component) {
    return entities[component.getOwningEntityID()];
}

Entity& EntityManager::getEntity(const Component* component) {
    return entities[component -> getOwningEntityID()];
}
