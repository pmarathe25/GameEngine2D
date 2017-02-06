#include "GameEngine2D/EntityManager.hpp"

EntityManager::EntityManager(sf::RenderWindow* window, int expectedNumEntities) : renderSystem(window, expectedNumEntities), physicsSystem(expectedNumEntities) {
    entities.reserve(expectedNumEntities);
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
}

void EntityManager::update(float frametime) {
    physicsSystem.update(frametime);
    sync();
    renderSystem.update();
}

bool EntityManager::attachComponent(int eID, const Component& component) {
    switch (component.getComponentID()) {
        case RENDER:
            getEntity(eID).registerComponent(RENDER, renderSystem.addComponent(static_cast<const RenderComponent&>(component), eID));
            break;
        case PHYSICS:
            getEntity(eID).registerComponent(PHYSICS, physicsSystem.addComponent(static_cast<const PhysicsComponent&>(component), eID));
            break;
    }
}

Entity& EntityManager::getEntity(int eID) {
    return entities[eID];
}


void EntityManager::sync() {
    for (int i = 0; i < physicsSystem.size(); ++i) {
        renderSystem.getComponent(getEntity(physicsSystem.getComponent(i).getOwningEntityID()).getComponentIndexByID(RENDER)).sprite.setPosition(physicsSystem.getComponent(i).position);
    }
}
