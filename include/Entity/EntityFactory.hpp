#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H
#include "ResourceManager.hpp"
#include "System/TransformSystem.hpp"
#include "System/StaticRenderSystem.hpp"
#include "System/DynamicRenderSystem.hpp"
#include <set>

typedef int Entity;
typedef std::set<Entity> EntityGroup;

namespace StealthEngine {
    enum EntityType {
        PLAYER = 0,
    };

    template <typename EntityManager>
    class EntityFactory {
        public:
            EntityFactory(EntityManager& entityManager, ResourceManager& resourceManager) : entityManager(entityManager), resourceManager(resourceManager) { }
            // Create a single entity.
            template <EntityType N = 0>
            Entity createEntity() {
                if constexpr (N == PLAYER) {
                    entityManager.get<StealthEngine::TransformSystem>().addComponent(entity);
                    entityManager.get<StealthEngine::DynamicRenderSystem>().addComponent(entity, resourceManager.get<sf::Texture>("res/player.png"));
                }
            }
            // Create a group of entities.
            template <EntityType N = 0>
            EntityGroup createEntityGroup(int numEntities) {
                EntityGroup newGroup;
                for (int i = 0; i < numEntities; ++i) {
                    newGroup.insert(createEntity<N>());
                }
                return newGroup;
            }
        private:
            EntityManager& entityManager;
            ResourceManager& resourceManager;
    };
} /* StealthEngine */

#endif
