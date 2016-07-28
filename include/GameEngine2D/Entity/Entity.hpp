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
        int getComponentIndexByID(componentID id);
        // Register a component with this entity.
        void registerComponent(std::pair<Component*, int> component);
        int deregisterComponent(componentID cID);
        void updateCommponent(componentID cID, int index);
        // Data members.
        sf::Vector2f position;
        int eID;
        std::map<componentID, int> components;
};

#endif
