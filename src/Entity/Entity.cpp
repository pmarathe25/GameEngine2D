#include "GameEngine2D/Entity/Entity.hpp"
#include "GameEngine2D/Component/RenderComponent.hpp"
#include "GameEngine2D/Component/PhysicsComponent.hpp"

Entity::Entity(int eID, const sf::Vector2f& position) {
    this -> eID = eID;
    this -> position = position;
}

int Entity::getComponentIndexByID(componentID id) {
    if (components.count(id) > 0) {
        return components.at(id);
    } else {
        return -1;
    }
}

void Entity::registerComponent(std::pair<Component*, int> component) {
    components[component.first -> cID] = component.second;
    component.first -> eID = this -> eID;
    switch (component.first -> cID) {
        case RENDER:
            static_cast<RenderComponent*>(component.first) -> sprite.setPosition(position);
            break;
        case PHYSICS:
            static_cast<PhysicsComponent*>(component.first) -> position = position;
            break;
    }
}

int Entity::deregisterComponent(componentID cID) {
    int index = getComponentIndexByID(cID);
    components.erase(cID);
    return index;
}

void Entity::updateCommponent(componentID cID, int index) {
    components.at(cID) = index;
}
