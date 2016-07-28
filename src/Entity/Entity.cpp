#include "GameEngine2D/Entity/Entity.hpp"
#include "GameEngine2D/Component/RenderComponent.hpp"

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
    component.first -> eID = eID;
    switch (component.first -> cID) {
        case RENDER:
            static_cast<RenderComponent*>(component.first) -> sprite.setPosition(position);
    }
}

int Entity::deregisterComponent(componentID cID) {
    int index = components.at(cID);
    components.erase(cID);
    return index;
}

void Entity::updateCommponent(componentID cID, int index) {
    components.at(cID) = index;
}
