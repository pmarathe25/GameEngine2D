#include "System/TransformSystem.hpp"

namespace StealthEngine {
    bool TransformSystem::addComponent(int eID, sf::Vector2f position, float rotation, sf::Vector2f scale) {
        // If the entity is not already in the system, add components for it.
        if (System<TransformSystem>::addComponent(eID)) {
            positions.emplace_back(position);
            rotations.emplace_back(rotation);
            scales.emplace_back(scale);
        }
    }

    bool TransformSystem::removeComponent(eID) {
        if (entityComponents.count(eID) > 0) {
            int index = entityComponents[eID];
            // First remove the old components by replacing them with the ones at the end.
            positions[index] = positions.back();
            rotations[index] = rotations.back();
            scales[index] = scales.back();
            // Now update the modified entity's mapping to reflect the change.
            int modifiedEntity = componentEntities.back();
        }
    }

} /* StealthEngine */
