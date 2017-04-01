#ifndef ENTITY_H
#define ENTITY_H
#include "GameEngine2D/Component/Component.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class Entity {
    public:
        Entity() {};
        // Get any type of component.
        int getComponentIndexByID(int cID);
        // Register a component with this entity and returns whether it successfully registered.
        bool registerComponent(int cID, int componentIndex);
        int deregisterComponent(int cID);
        void updateCommponent(int cID, int index);
    private:
        // Data members.
        std::map<int, int> components;
};

#endif
