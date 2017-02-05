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
