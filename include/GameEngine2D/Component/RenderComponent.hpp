#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H
#include "GameEngine2D/Component/Component.hpp"
#include <SFML/Graphics.hpp>

class RenderComponent : public Component {
    public:
        RenderComponent(const sf::Texture& texture, const sf::Vector2f& position = sf::Vector2f(0, 0));
        sf::Sprite sprite;
        bool bHasPhysics = false;
};

#endif
