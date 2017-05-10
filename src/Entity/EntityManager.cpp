#include "GameEngine2D/Entity/EntityManager.hpp"

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

Entity& EntityManager::getEntity(int eID) {
    return entities[eID];
}

Entity& EntityManager::getEntity(const Component& component) {
    return entities[component.getOwningEntityID()];
}

Entity& EntityManager::getEntity(const Component* component) {
    return entities[component -> getOwningEntityID()];
}
