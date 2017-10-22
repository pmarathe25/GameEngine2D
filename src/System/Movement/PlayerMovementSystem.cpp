#include "System/Movement/PlayerMovementSystem.hpp"

namespace StealthEngine {
    float& PlayerMovementSystem::movementSpeed(int eID) {
        return MovementSystem::get(eID, movementSpeeds);
    }

    float PlayerMovementSystem::movementSpeed(int eID) const {
        return MovementSystem::get(eID, movementSpeeds);
    }
} /* StealthEngine */
