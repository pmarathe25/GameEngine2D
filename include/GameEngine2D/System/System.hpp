#ifndef SYSTEM_H
#define SYSTEM_H
#include "GameEngine2D/Component/Component.hpp"
#include <utility>
#include <vector>

template <class ComponentType>
class System {
    public:
        System(int expectedNumEntities) {
            components.reserve(expectedNumEntities);
        }
        // Add a component to the system and returns a pointer to it and index (to register it with the entity).
        int addComponent(const ComponentType& newComponent, int eID) {
            components.push_back(newComponent);
            components.back().setOwningEntityID(eID);
            return components.size() - 1;
        }
        // Remove a component from the system and returns the eID of the owning entity of the other modified component.
        int removeComponent(int index) {
            // Swap the component to remove with the last component.
            components.at(index) = components.back();
            // Pop.
            components.pop_back();
            // Return the index of the other entity that was modified.
            if (index < components.size()) {
                return components.at(index).getOwningEntityID();
            } else {
                return -1;
            }
        }
        // Get a pointer to a component.
        const ComponentType& getComponent(int index) {
            if (index >= 0 && index < components.size()) {
                return components.at(index);
            } else {
                return nullptr;
            }
        }
        int size() {
            return components.size();
        }
    protected:
        std::vector<ComponentType> components;
};

#endif
