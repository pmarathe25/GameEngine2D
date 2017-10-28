#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H
#include <tuple>

namespace StealthEngine {
    template <typename... Systems>
    class SystemManager {
        public:
            SystemManager(Systems&... systems) : systems(systems...) { }
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
            // Get system by its position
            template <int N = 0, typename SystemType>
            SystemType& get() {
                static_assert(sizeof...(Systems) != 0, "No systems present");
                return std::get<N>(systems);
            }
            // Destroy and remove from systems if present.
            bool destroyEntity(int entity) {
                if constexpr (sizeof...(Systems) != 0) {
                    destroyEntityUnpacker(entity, std::index_sequence_for<Systems...>{});
                    return true;
                }
                return false;
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
            void destroyEntityUnpacker(int entity, std::index_sequence<S...>) {
                destroyEntityRecursive(entity, std::get<S>(systems)...);
            }

            template <typename FrontSystem, typename... BackSystems>
            void destroyEntityRecursive(int entity, FrontSystem& front, BackSystems&... back) {
                front.removeComponent(entity);
                if constexpr (sizeof...(back) != 0) {
                    destroyEntityRecursive(entity, back...);
                }
            }
            // Keep track of systems.
            std::tuple<Systems&...> systems;
    };
} /* StealthEngine */

#endif