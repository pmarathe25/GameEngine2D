#include "GameEngine2D/Component/Component.hpp"

Component::Component(componentID id) {
    cID = id;
}

int Component::getComponentID() {
    return cID;
}

int Component::getOwningEntityID() {
    return eID;
}

void setOwningEntityID(int eID) {
    this -> eID = eID;
}
