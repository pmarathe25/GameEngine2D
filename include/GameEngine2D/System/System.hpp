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
        std::pair<Component*, int> addComponent(const ComponentType& newComponent) {
            if (components.size() + 1 >= components.capacity()) {
                components.reserve(components.capacity() * 2);
            }
            components.push_back(newComponent);
            return std::make_pair(&components.back(), components.size() - 1);
        }
        // Remove a component from the system and returns the eID of the owning entity of the other modified component.
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
        // Get a pointer to a component.
        ComponentType* getComponentByIndex(int index) {
            if (index >= 0 && index < components.size()) {
                return &components.at(index);
            } else {
                return nullptr;
            }
        }
        // Java-Iterator-like functions.
        bool hasNext() {
            if (iteratorIndex < components.size()) {
                return true;
            } else {
                iteratorIndex = 0;
                return false;
            }
        }
        ComponentType* next() {
            // Get a component and then increment the iterator.
            return getComponentByIndex(iteratorIndex++);
        }
    protected:
        std::vector<ComponentType> components;
    private:
        int iteratorIndex;
};

#endif
