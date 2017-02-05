#ifndef ENTITY_H
#define ENTITY_H
#include "GameEngine2D/Component/Component.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <utility>

class Entity {
    public:
        Entity(int eID, const sf::Vector2f& position);
        // Get any type of component.
        int getComponentIndexByID(componentID cID);
        // Register a component with this entity and returns whether it successfully registered.
        bool registerComponent(componentID cID, int componentIndex);
        int deregisterComponent(componentID cID);
        void updateCommponent(componentID cID, int index);
        // Position.
        sf::Vector2f& position();
    private:
        // Data members.
        sf::Vector2f position;
        int eID;
        std::map<componentID, int> components;
};

#endif
