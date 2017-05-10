#ifndef ENTITY_H
#define ENTITY_H
#include "GameEngine2D/Component/Component.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class Entity {
    public:
        Entity();
        // Get any type of component.
        int getComponentIndexByID(int systemID);
        // Register a component with this entity and returns whether it successfully registered.
        bool registerComponent(int systemID, int componentIndex);
        // Remove a component.
        int deregisterComponent(int systemID);
        // Update an exsiting component's index.
        void updateCommponent(int systemID, int index);
        // Get the component map.
        std::map<int, int>& getComponentMap();
    private:
        // Data members.
        std::map<int, int> components;
};

#endif
