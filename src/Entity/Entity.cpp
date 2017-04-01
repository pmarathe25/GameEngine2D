#include "GameEngine2D/Entity/Entity.hpp"
#include "GameEngine2D/Component/RenderComponent.hpp"
#include "GameEngine2D/Component/PhysicsComponent.hpp"

int Entity::getComponentIndexByID(int cID) {
    if (components.count(cID) > 0) {
        return components.at(cID);
    } else {
        return -1;
    }
}

bool Entity::registerComponent(int cID, int componentIndex) {
    if (components.count(cID) > 0) {
        return false;
    } else {
        components[cID] = componentIndex;
        return true;
    }
}
