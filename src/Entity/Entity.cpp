#include "GameEngine2D/Entity/Entity.hpp"

Entity::Entity(const sf::Vector2f& position) {
    this -> position = position;
}

Component* Entity::getComponentByID(componentID id) {
    if (components.count(id) > 0) {
        return components.at(id);
    } else {
        return nullptr;
    }
}

void Entity::addComponent(Component* newComponent) {
    components[newComponent -> cID] = newComponent;
}
