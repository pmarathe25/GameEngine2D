#ifndef ENTITY_H
#define ENTITY_H
#include "GameEngine2D/Component/Component.hpp"
#include <SFML/Graphics.hpp>
#include <map>

class Entity {
    public:
        Entity(const sf::Vector2f& position);
        Component* getComponentByID(componentID id);
        void addComponent(Component* newComponent);
        sf::Vector2f position;
    private:
        std::map<componentID, Component*> components;
};

#endif
