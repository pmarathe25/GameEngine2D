#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H
#include "GameEngine2D/Component/Component.hpp"
#include <SFML/Graphics.hpp>

class CollisionComponent : public Component {
    public:
        CollisionComponent(const sf::Vector2f& boundingBox, const sf::Vector2f& position = sf::Vector2f(0, 0));
        int physicsComponentIndex = -1;
        sf::Vector2f boundingBox;
        sf::Vector2f position;
};

#endif
