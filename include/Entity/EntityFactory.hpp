#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H
#include "ResourceManager.hpp"
#include "System/TransformSystem.hpp"
#include "System/Render/StaticRenderSystem.hpp"
#include "System/Render/DynamicRenderSystem.hpp"
#include <algorithm>
#include <vector>

typedef int Entity;

namespace StealthEngine {
    enum EntityType {
        PLAYER = 0,
    };

    class EntityGroup : public std::vector<Entity> {
        template <typename EntityManager>
        friend class EntityFactory;
        public:
            void push_back(const Entity& entity) {
                if (std::find(begin(), end(), entity) == end()) {
                    std::vector<Entity>::push_back(entity);
                }
            }

            void push_back(Entity&& entity) {
                if (std::find(begin(), end(), entity) == end()) {
                    std::vector<Entity>::push_back(std::move(entity));
                }
            }

            bool removeFromGroup(Entity entity) {
                for (int i = 0; i < size(); ++i) {
                    if ((*this)[i] == entity) {
                        (*this)[i] = back();
                        pop_back();
                        return true;
                    }
                }
                return false;
            }
        private:
            void push_back_unsafe(Entity entity) {
                std::vector<Entity>::push_back(entity);
            }
    };

    template <typename EntityManager>
    class EntityFactory {
        public:
            EntityFactory(EntityManager& entityManager, ResourceManager& resourceManager) : entityManager(entityManager), resourceManager(resourceManager) { }
            // Create a single entity.
            template <EntityType N = 0>
            Entity createEntity() {
                Entity entity = entityManager.createEntity();
                if constexpr (N == PLAYER) {
                    entityManager.template get<StealthEngine::TransformSystem>().addComponent(entity);
                    entityManager.template get<StealthEngine::DynamicRenderSystem>().addComponent(entity, resourceManager.get<sf::Texture>("res/player.png"));
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
                return entityManager.destroyEntity(entity);
            }
            // Destroy an entity after removing it from a group.
            bool destroyEntity(EntityGroup& entityGroup, Entity entity) {
                entityGroup.removeFromGroup(entity);
                return entityManager.destroyEntity(entity);
            }
            // Destroy an entity group.
            void destroyEntityGroup(EntityGroup& entityGroup) {
                for (auto& entity : entityGroup) {
                    entityManager.destroyEntity(entity);
                }
                entityGroup = {};
            }
        private:
            EntityManager& entityManager;
            ResourceManager& resourceManager;
    };
} /* StealthEngine */

#endif
