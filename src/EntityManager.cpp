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

void EntityManager::update(float frametime) {
    // physicsSystem.update(frametime);
    // sync();
    // renderSystem.update();
}

Entity& EntityManager::getEntity(int eID) {
    return entities[eID];
}


void EntityManager::sync() {
    // for (int i = 0; i < physicsSystem.size(); ++i) {
    //     renderSystem.getComponent(getEntity(physicsSystem.getComponent(i).getOwningEntityID()).getComponentIndexByID(RENDER)).sprite.setPosition(physicsSystem.getComponent(i).position);
    // }
}
