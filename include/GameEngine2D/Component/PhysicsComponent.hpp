#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H
#include "GameEngine2D/Component/Component.hpp"
#include <SFML/Graphics.hpp>

class PhysicsComponent : public Component {
    public:
        PhysicsComponent(const sf::Vector2f& velocity);
        void setPosition(const sf::Vector2f& position);
    private:
        sf::Vector2f position;
        sf::Vector2f velocity;
};

#endif
