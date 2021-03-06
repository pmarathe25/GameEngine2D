#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H
#include "GameEngine2D/Component/Component.hpp"
#include <SFML/Graphics.hpp>

class RenderComponent : public Component {
    public:
        RenderComponent(const sf::Texture& texture);
        sf::Sprite sprite;
};

#endif
