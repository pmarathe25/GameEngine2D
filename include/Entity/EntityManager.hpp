#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include <tuple>
#include <utility>
#include <queue>

typedef int Entity;

namespace StealthEngine {
    template <typename... Systems>
    class EntityManager {
        public:
            EntityManager(Systems&... systems) : systems(systems...) { }
            Entity createEntity();

            bool destroyEntity(Entity entity) {
                if constexpr (sizeof...(Systems) != 0) {
                    destroyEntityUnpacker(entity, std::index_sequence_for<Systems...>{});
                }
                freeList.push(entity);
            }
        private:
            template <int... S>
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
            std::tuple<Systems&...> systems;
            std::queue<int> freeList;
            Entity currentEntity = 0;
    };
} /* StealthEngine */

#endif
