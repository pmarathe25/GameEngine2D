#ifndef WORLD_H
#define WORLD_H
#include "EventManager.hpp"
#include <SFML/System.hpp>
#include <vector>
#include <set>

typedef int Entity;

namespace StealthEngine {
    class World {
        public:
            World(EventManager& eventManager) : eventManager(eventManager) { }
            Entity createEntity(const sf::Vector2f& position = {}, float rotation = 0, const sf::Vector2f& scale = {});
            bool destroyEntity(Entity entity);
            // Constant getters.
            const sf::Vector2f& getPosition(Entity eID) const;

            // Setters that will generate events.
            void setPosition(Entity eID, const sf::Vector2f& position);
        private:
            // Event manager.
            EventManager& eventManager;
            // Maintain transforms of all entities.
            std::vector<sf::Vector2f> positions;
            std::vector<float> rotations;
            std::vector<sf::Vector2f> scales;
            // Destroyed entities
            std::set<Entity> freeList;
            Entity currentEntity = 0;
    };
} /* StealthEngine */

#endif
