#include "System/TransformSystem.hpp"

namespace StealthEngine {
    void TransformSystem::update(float frametime) {

    }

    bool TransformSystem::addComponent(int eID, sf::Vector2f position, float rotation, sf::Vector2f scale) {
        // If the entity is not already in the system, add components for it.
        return System<TransformSystem>::addComponent(eID, positions, position, rotations, rotation, scales, scale);
    }

    bool TransformSystem::removeComponent(int eID) {
        // Remove the components of the entity if it exits.
        return System<TransformSystem>::removeComponent(eID, positions, rotations, scales);
    }

    sf::Vector2f& TransformSystem::position(int eID) {
        return System<TransformSystem>::get(eID, positions);
    }

    float& TransformSystem::rotation(int eID) {
        return System<TransformSystem>::get(eID, rotations);
    }

    sf::Vector2f& TransformSystem::scale(int eID) {
        return System<TransformSystem>::get(eID, scales);
    }

    const sf::Vector2f& TransformSystem::position(int eID) const {
        return System<TransformSystem>::get(eID, positions);
    }

    const float& TransformSystem::rotation(int eID) const {
        return System<TransformSystem>::get(eID, rotations);
    }

    const sf::Vector2f& TransformSystem::scale(int eID) const {
        return System<TransformSystem>::get(eID, scales);
    }

} /* StealthEngine */
