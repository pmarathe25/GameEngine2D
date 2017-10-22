#ifndef SYSTEM_H
#define SYSTEM_H
#include <unordered_map>
#include <vector>

namespace StealthEngine {
    template <typename SystemType>
    class System {
        public:
            System() { }
            // Call the child class' implementation.
            void update(float frametime) {
                static_cast<SystemType*>(this) -> update(frametime);
            }

            bool hasEntity(int eID) const {
                return entityComponent.count(eID) > 0;
            }

            // Add components to an entity and return whether the components were successfully added.
            template <typename... Args>
            bool addComponent(int eID, Args&... args) {
                // Check if this entity already exists and if it does, disallow adding a component.
                if (entityComponent.count(eID) > 0) {
                    throw std::invalid_argument("Cannot add duplicate component to entity");
                }
                // Recursively add all components.
                if constexpr (sizeof...(args) != 0) {
                    addComponentRecursive(args...);
                }
                // Update the entity -> component mapping and the component -> entity mapping
                entityComponent[eID] = componentEntity.size();
                componentEntity.emplace_back(eID);
                return true;
            }

            // Removes components belonging to an entity and return whether the components were successfully removed.
            template <typename... Args>
            bool removeComponent(int eID, Args&... args) {
                if (entityComponent.count(eID) > 0) {
                    int index = entityComponent[eID];
                    // Recursively remove all components.
                    if constexpr (sizeof...(args) != 0) {
                        removeComponentRecursive(index, args...);
                    }
                    // Now update the modified entity's mapping to reflect the change.
                    int modifiedEntity = componentEntity.back();
                    entityComponent[modifiedEntity] = index;
                    componentEntity.pop_back();
                    return true;
                }
                return false;
            }
        protected:
            template <typename T>
            T& get(int eID, std::vector<T>& vec) {
                return vec[entityComponent[eID]];
            }

            template <typename T>
            const T& get(int eID, const std::vector<T>& vec) const {
                return vec[entityComponent.at(eID)];
            }

            template <typename Vec, typename Elem, typename... Args>
            void addComponentRecursive(Vec& vec, Elem& elem, Args&... args) {
                vec.emplace_back(elem);
                if constexpr (sizeof...(args) != 0) {
                    addComponentRecursive(args...);
                }
            }

            template <typename Vec, typename... Args>
            void removeComponentRecursive(int index, Vec& vec, Args&... args) {
                // Remove elements by swapping them with the last element.
                vec[index] = vec.back();
                vec.pop_back();
                if constexpr (sizeof...(args) != 0) {
                    removeComponentRecursive(index, args...);
                }
            }

            // All systems contain a map of entityIDs to componentIndex
            std::unordered_map<int, int> entityComponent;
            std::vector<int> componentEntity;
    };
} /* StealthEngine */

#endif
