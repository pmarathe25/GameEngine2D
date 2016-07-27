#include "GameEngine2D/EntityManager.hpp"
#include "GameEngine2D/Component/RenderComponent.hpp"

EntityManager::EntityManager(sf::RenderWindow* window, int expectedNumEntities) : renderSystem(window, expectedNumEntities) {
    entities.reserve(expectedNumEntities);
}

int EntityManager::createEntity(const sf::Vector2f& position) {
    int newID;
    if (!freeIDs.empty()) {
        newID = freeIDs.back();
        freeIDs.pop_back();
        entities.at(newID) = Entity(position);
    } else {
        newID = entities.size();
        entities.push_back(Entity(position));
    }
    return newID;
}

void EntityManager::destroyEntity(int eID) {

}

void EntityManager::update(float frametime) {
    renderSystem.update();
}

void EntityManager::attachComponent(int eID, const RenderComponent& component) {
    entities.at(eID).registerComponent(renderSystem.addComponent(component));
}

void EntityManager::detachComponent(int eID, componentID cID) {

}

Entity& EntityManager::getEntity(int eID) {
    return entities.at(eID);
}
