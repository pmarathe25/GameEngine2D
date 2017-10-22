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
            // Add components to an entity and return whether the components were successfully added.
            template <typename... Args>
            bool addComponent(int eID, Args&... args) {
                // Check if this entity already exists and if it does, disallow adding a component.
                if (entityComponents.count(eID) > 0) {
                    throw std::invalid_argument("Cannot add duplicate component to entity");
                }
                // Recursively add all components.
                if constexpr (sizeof...(args) != 0) {
                    addComponentRecursive(args...);
                }
                // Update the entity -> component mapping and the component -> entity mapping
                entityComponents[eID] = componentEntities.size();
                componentEntities.emplace_back(eID);
                return true;
            }
            // Removes components belonging to an entity and return whether the components were successfully removed.
            template <typename... Args>
            bool removeComponent(int eID, Args&... args) {
                if (entityComponents.count(eID) > 0) {
                    int index = entityComponents[eID];
                    // Recursively remove all components.
                    if constexpr (sizeof...(args) != 0) {
                        removeComponentRecursive(index, args...);
                    }
                    // Now update the modified entity's mapping to reflect the change.
                    int modifiedEntity = componentEntities.back();
                    entityComponents[modifiedEntity] = index;
                    componentEntities.pop_back();
                    return true;
                }
                return false;
            }
        protected:
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
            std::unordered_map<int, int> entityComponents;
            std::vector<int> componentEntities;
    };
} /* StealthEngine */

#endif
