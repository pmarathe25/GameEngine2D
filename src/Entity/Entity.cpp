#include "GameEngine2D/Entity/Entity.hpp"
#include "GameEngine2D/Component/RenderComponent.hpp"
#include "GameEngine2D/Component/PhysicsComponent.hpp"

Entity::Entity(int eID, const sf::Vector2f& position) {
    this -> eID = eID;
    this -> position = position;
}

int Entity::getComponentIndexByID(componentID cID) {
    if (components.count(cID) > 0) {
        return components.at(cID);
    } else {
        return -1;
    }
}

bool Entity::registerComponent(componentID cID, int componentIndex) {
    if (components.count(cID) > 0) {
        return false;
    } else {
        components[cID] = componentIndex;
        return true;
    }
}

sf::Vector2f& Entity::position() {
    return position;
}
