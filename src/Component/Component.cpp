#include "GameEngine2D/Component/Component.hpp"

Component::Component(componentID id) {
    cID = id;
}

int Component::getComponentID() const {
    return cID;
}

int Component::getOwningEntityID() const {
    return eID;
}

void Component::setOwningEntityID(int eID) {
    this -> eID = eID;
}
