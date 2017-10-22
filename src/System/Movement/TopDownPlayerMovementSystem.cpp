#include "System/Movement/TopDownPlayerMovementSystem.hpp"

#include <iostream>

namespace StealthEngine {
    void TopDownPlayerMovementSystem::update(float frametime) {
        int deltaX = sf::Keyboard::isKeyPressed(keymap[MOVE_RIGHT]) - sf::Keyboard::isKeyPressed(keymap[MOVE_LEFT]);
        int deltaY = sf::Keyboard::isKeyPressed(keymap[MOVE_DOWN]) - sf::Keyboard::isKeyPressed(keymap[MOVE_UP]);
        // Loop over all components and apply the changes.
        for (int i = 0; i < movementSpeeds.size(); ++i) {
            int eID = componentEntity[i];
            float movementSpeed = movementSpeeds[i] * frametime * ((deltaX && deltaY) * DIAGONALIZATION_FACTOR + !(deltaX && deltaY));
            try {
                transformSystem.position(eID) += {deltaX * movementSpeed, deltaY * movementSpeed};
            } catch (std::invalid_argument& e) {
                throw std::invalid_argument("TopDownPlayerMovementSystem cannot update entities with no Transform component.");
            }
        }
    }
} /* StealthEngine */
