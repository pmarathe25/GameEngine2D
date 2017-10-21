#ifndef SYSTEM_H
#define SYSTEM_H
#include <unordered_map>
#include <vector>

namespace StealthEngine {
    // Base case
    template <typename Vec, typename Elem>
    void addElementsToVectors(Vec& vec, Elem& elem) {
        vec.push_back(elem);
    }

    template <typename Vec, typename Elem, typename... Args>
    void addElementsToVectors(Vec& vec, Elem& elem, Args&... args) {
        vec.push_back(elem);
        addElementsToVectors(args...);
    }

    // Base case
    template <typename Vec, typename Elem>
    void removeElementsFromVectors(int index, Vec& vec, Elem& elem) {
        vec[index] = vec.back();
        vec.pop_back();
    }

    template <typename Vec, typename Elem, typename... Args>
    void removeElementsFromVectors(int index, Vec& vec, Elem& elem, Args&... args) {
        vec[index] = vec.back();
        vec.pop_back();
        removeElementsFromVectors(index, args...);
    }

    template <typename SystemType>
    class System {
        public:
            System() { }
            // Call the child class' implementation.
            void update(float frametime) {
                static_cast<SystemType*>(this) -> update(frametime);
            }
            bool addComponent(int eID) {
                // Check if this entity already exists and if it does, disallow adding a component.
                if (entityComponents.count(eID) > 0) {
                    return false;
                }
                // Update the entity -> component mapping and the component -> entity mapping
                entityComponents[eID] = componentEntities.size();
                componentEntities.push_back(eID);
                return true;
            }
        protected:
            // All systems contain a map of entityIDs to componentIndex
            std::unordered_map<int, int> entityComponents;
            std::vector<int> componentEntities;
    };
} /* StealthEngine */

#endif
