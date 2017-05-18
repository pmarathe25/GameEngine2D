#include "GameEngine2D/Entity/Entity.hpp"
#include "GameEngine2D/Component/RenderComponent.hpp"
#include "GameEngine2D/Component/PhysicsComponent.hpp"

Entity::Entity() {

}

int Entity::getComponentIndexByID(int systemID) {
    if (components.count(systemID) > 0) {
        return components[systemID];
    } else {
        return -1;
    }
}

bool Entity::registerComponent(int systemID, int componentIndex) {
    if (components.count(systemID) > 0) {
        return false;
    } else {
        components[systemID] = componentIndex;
        return true;
    }
}

int Entity::deregisterComponent(int systemID) {
    components.erase(systemID);
}

void Entity::updateCommponent(int systemID, int index) {
    components[systemID] = index;
}

std::unordered_map<int, int>& Entity::getComponentMap() {
    return components;
}

bool Entity::isActive() {
    return bActive;
}

void Entity::activate() {
    bActive = true;
}

void Entity::deactivate() {
    bActive = false;
    components.clear();
}
