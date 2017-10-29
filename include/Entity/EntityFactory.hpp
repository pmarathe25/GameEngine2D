#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H
#include "Entity/EntityGroup.hpp"
#include "ResourceManager.hpp"
#include <algorithm>
#include <vector>

namespace StealthEngine {
    enum EntityType {
        PLAYER = 0,
    };

    template <typename SystemManager>
    class EntityFactory {
        public:
            EntityFactory(World& world, SystemManager& systemManager, ResourceManager& resourceManager) :
                world(world), systemManager(systemManager), resourceManager(resourceManager) { }
            // Create a single entity.
            template <EntityType N = 0>
            Entity createEntity() {
                Entity entity = world.createEntity();
                if constexpr (N == PLAYER) {
                    systemManager.template get<RenderSystem>().addComponent(entity, resourceManager.get<sf::Texture>("res/player.png"));
                }
                return entity;
            }
            // Create a group of entities.
            template <EntityType N = 0>
            EntityGroup createEntityGroup(int numEntities) {
                EntityGroup newGroup;
                for (int i = 0; i < numEntities; ++i) {
                    newGroup.push_back_unsafe(createEntity<N>());
                }
                return newGroup;
            }
            // Destroy a single entity either standalone or from a group.
            bool destroyEntity(Entity entity) {
                systemManager.destroyEntity(entity);
                return world.destroyEntity(entity);
            }
            // Destroy an entity after removing it from a group.
            bool destroyEntity(EntityGroup& entityGroup, Entity entity) {
                entityGroup.removeFromGroup(entity);
                return destroyEntity(entity);
            }
            // Destroy an entity group.
            void destroyEntityGroup(EntityGroup& entityGroup) {
                for (auto& entity : entityGroup) {
                    destroyEntity(entity);
                }
                entityGroup = {};
            }
        private:
            World& world;
            SystemManager& systemManager;
            ResourceManager& resourceManager;
    };
} /* StealthEngine */

#endif
