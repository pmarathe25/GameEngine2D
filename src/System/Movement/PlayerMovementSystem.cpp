#include "System/Movement/PlayerMovementSystem.hpp"

namespace StealthEngine {
    bool PlayerMovementSystem::addComponent(int eID, float movementSpeed) {
        if (!transformSystem.hasEntity(eID)) {
            throw std::invalid_argument("Cannot add Player Movement Component to an Entity with no Transform component.");
        }
        return MovementSystem::addComponent(eID, movementSpeeds, movementSpeed);
    }

    bool PlayerMovementSystem::removeComponent(int eID) {
        return MovementSystem::removeComponent(eID);
    }

    float& PlayerMovementSystem::movementSpeed(int eID) {
        return MovementSystem::get(eID, movementSpeeds);
    }

    float PlayerMovementSystem::movementSpeed(int eID) const {
        return MovementSystem::get(eID, movementSpeeds);
    }
} /* StealthEngine */
