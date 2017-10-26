#include "World.hpp"

namespace StealthEngine {
    Entity World::createEntity(const sf::Vector2f& position, float rotation, const sf::Vector2f& scale) {
        if (!freeList.empty()) {
            auto lastElem = freeList.end();
            Entity newEID = *(--lastElem);
            freeList.erase(lastElem);
            // Add transform.
            positions[newEID] = position;
            rotations[newEID] = rotation;
            scales[newEID] = scale;
            return newEID;
        } else {
            positions.emplace_back(position);
            rotations.emplace_back(rotation);
            scales.emplace_back(scale);
            return currentEntity++;
        }
    }

    bool World::destroyEntity(Entity entity) {
        // Only destroy an entity if it actually exists.
        if (entity < currentEntity) {
            freeList.insert(entity);
            return true;
        }
        return false;
    }

    void World::setPosition(Entity eID, const sf::Vector2f& position) {
        positions[eID] = position;
        eventManager.post<EventManager::POSITION_CHANGED>(std::forward<Entity>(eID), std::forward<const sf::Vector2f&>(position));
        // eventManager.post<EventManager::POSITION_CHANGED>(eID, position);
    }

} /* StealthEngine */
