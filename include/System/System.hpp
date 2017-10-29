#ifndef SYSTEM_H
#define SYSTEM_H
#include "World.hpp"
#include <unordered_map>
#include <vector>

namespace StealthEngine {
    template <typename SystemType>
    class System {
        public:
            System(World& world, EventManager& eventManager) : world(world), eventManager(eventManager) { }
            void update(float frametime) {
                // Call the child class' implementation.
                static_cast<SystemType*>(this) -> update(frametime);
            }
            // Check if the system has a component belonging to an entity.
            bool hasEntity(Entity eID) const {
                return entityComponent.count(eID) > 0;
            }
            // Add components to an entity and return whether the components were successfully added.
            template <typename... Args>
            bool addComponent(Entity eID, Args&&... args) {
                // Check if this entity already exists and if it does, disallow adding a component.
                if (entityComponent.count(eID) > 0) {
                    throw std::invalid_argument("Cannot add duplicate component to entity");
                }
                // Recursively add all components.
                if constexpr (sizeof...(args) != 0) {
                    addComponentRecursive(std::forward<Args>(args)...);
                }
                // Update the entity -> component mapping and the component -> entity mapping
                entityComponent[eID] = componentEntity.size();
                componentEntity.emplace_back(eID);
                return true;
            }
            // Removes components belonging to an entity and return whether the components were successfully removed.
            template <typename... Args>
            bool removeComponent(Entity eID, Args&&... args) {
                if (entityComponent.count(eID) > 0) {
                    int index = entityComponent[eID];
                    // Recursively remove all components.
                    if constexpr (sizeof...(args) != 0) {
                        removeComponentRecursive(index, std::forward<Args>(args)...);
                    }
                    // Now update the modified entity's mapping to reflect the change.
                    int modifiedEntity = componentEntity.back();
                    entityComponent[modifiedEntity] = index;
                    // Now remove from the old entity.
                    entityComponent.erase(eID);
                    componentEntity.pop_back();
                    return true;
                }
                return false;
            }
        protected:
            template <typename... Args>
            void swap(int indexA, int indexB, Args&&... args) {
                // First update the mappings.
                Entity eIDA = componentEntity[indexA], eIDB = componentEntity[indexB];
                entityComponent[eIDA] = indexB;
                entityComponent[eIDB] = indexA;
                componentEntity[indexA] = eIDB;
                componentEntity[indexB] = eIDA;
                if constexpr (sizeof...(args) != 0) {
                    swapRecursive(indexA, indexB, std::forward<Args>(args)...);
                }
            }

            template <typename Vec, typename... Args>
            void swapRecursive(int indexA, int indexB, Vec& vec, Args&&... args) {
                auto temp = vec[indexA];
                vec[indexA] = vec[indexB];
                vec[indexB] = temp;
                if constexpr (sizeof...(args) != 0) {
                    swapRecursive(indexA, indexB, std::forward<Args>(args)...);
                }
            }
            // Get an element from a vector based on an entity ID.
            template <typename T>
            T& get(Entity eID, std::vector<T>& vec) {
                try {
                    return vec[entityComponent.at(eID)];
                } catch (std::out_of_range& e) {
                    throw std::invalid_argument("Entity not present in system.");
                }
            }

            template <typename T>
            const T& get(Entity eID, const std::vector<T>& vec) const {
                try {
                    return vec[entityComponent.at(eID)];
                } catch (std::out_of_range& e) {
                    throw std::invalid_argument("Entity not present in system.");
                }
            }

            template <typename Vec, typename Elem, typename... Args>
            void addComponentRecursive(Vec& vec, Elem&& elem, Args&&... args) {
                vec.emplace_back(std::forward<Elem>(elem));
                if constexpr (sizeof...(args) != 0) {
                    addComponentRecursive(std::forward<Args>(args)...);
                }
            }

            template <typename Vec, typename... Args>
            void removeComponentRecursive(int index, Vec& vec, Args&&... args) {
                // Remove elements by swapping them with the last element.
                vec[index] = vec.back();
                vec.pop_back();
                if constexpr (sizeof...(args) != 0) {
                    removeComponentRecursive(index, std::forward<Args>(args)...);
                }
            }

            World& world;
            EventManager& eventManager;
            // All systems contain a map of entityIDs to componentIndex
            std::unordered_map<int, int> entityComponent;
            std::vector<int> componentEntity;
    };
} /* StealthEngine */

#endif
