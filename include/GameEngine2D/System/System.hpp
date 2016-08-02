#ifndef SYSTEM_H
#define SYSTEM_H
#include "GameEngine2D/Component/Component.hpp"
#include <vector>

template <class ComponentType>
class System {
    public:
        System(int expectedNumEntities) {
            components.reserve(expectedNumEntities);
        }
        // Add a component to the system.
        std::pair<Component*, int> addComponent(const ComponentType& newComponent) {
            if (components.size() + 1 >= components.capacity()) {
                components.reserve(components.capacity() * 2);
            }
            components.push_back(newComponent);
            return std::make_pair(&components.back(), components.size() - 1);
        }
        // Remove a component from the system.
        int removeComponent(int index) {
            // Swap the component to remove with the last component.
            components.at(index) = components.back();
            // Pop.
            components.pop_back();
            // Return the index of the other entity that was modified.
            if (index < components.size()) {
                return components.at(index).eID;
            } else {
                return -1;
            }
        }
    protected:
        std::vector<ComponentType> components;
};

#endif
