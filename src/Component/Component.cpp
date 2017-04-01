#include "GameEngine2D/Component/Component.hpp"

Component::Component() {
}

int Component::getOwningEntityID() const {
    return eID;
}

void Component::setOwningEntityID(int eID) {
    this -> eID = eID;
}
