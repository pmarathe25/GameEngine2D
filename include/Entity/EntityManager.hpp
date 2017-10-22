#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include <tuple>
#include <utility>
#include <typeinfo>
#include <queue>

typedef int Entity;

namespace StealthEngine {
    template <typename... Systems>
    class EntityManager {
        public:
            EntityManager(Systems&... systems) : systems(systems...) { }
            // Update all systems
            void update(float frametime) {
                if constexpr (sizeof...(Systems) != 0) {
                    updateUnpacker(frametime, std::index_sequence_for<Systems...>{});
                }
            }
            // Get a system of certain type
            template <typename SystemType>
            SystemType& get() {
                static_assert(sizeof...(Systems) != 0, "No systems present");
                return getUnpacker<SystemType>(std::index_sequence_for<Systems...>{});
            }
            // Return a new entity (or a previously deleted one)
            Entity createEntity() {
                if (!freeList.empty()) {
                    Entity newEID = freeList.front();
                    freeList.pop();
                    return newEID;
                }
                return currentEntity++;
            }
            // Destroy and remove from systems if present.
            bool destroyEntity(Entity entity) {
                if constexpr (sizeof...(Systems) != 0) {
                    destroyEntityUnpacker(entity, std::index_sequence_for<Systems...>{});
                }
                freeList.push(entity);
                return true;
            }
        private:
            // Update
            template <size_t... S>
            void updateUnpacker(float frametime, std::index_sequence<S...>) {
                    updateRecursive(frametime, std::get<S>(systems)...);
            }

            template <typename FrontSystem, typename... BackSystems>
            void updateRecursive(float frametime, FrontSystem& front, BackSystems&... back) {
                front.update(frametime);
                if constexpr (sizeof...(back) != 0) {
                    updateRecursive(frametime, back...);
                }
            }

            // Get function
            template <typename SystemType, size_t... S>
            SystemType& getUnpacker(std::index_sequence<S...>) {
                return getRecursive<SystemType>(std::get<S>(systems)...);
            }

            template <typename SystemType, typename FrontSystem, typename... BackSystems>
            SystemType& getRecursive(FrontSystem& front, BackSystems&... back) {
                if constexpr (std::is_same<FrontSystem, SystemType>::value) {
                    return front;
                } else {
                    return getRecursive<SystemType>(back...);
                }
            }

            // Destroy entity
            template <size_t... S>
            void destroyEntityUnpacker(Entity entity, std::index_sequence<S...>) {
                destroyEntityRecursive(entity, std::get<S>(systems)...);
            }

            template <typename FrontSystem, typename... BackSystems>
            void destroyEntityRecursive(Entity entity, FrontSystem& front, BackSystems&... back) {
                front.removeComponent(entity);
                if constexpr (sizeof...(back) != 0) {
                    destroyEntityRecursive(entity, back...);
                }
            }
            // Keep track of systems.
            std::tuple<Systems&...> systems;
            std::queue<int> freeList;
            Entity currentEntity = 0;
    };
} /* StealthEngine */

#endif
