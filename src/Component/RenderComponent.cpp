#include "GameEngine2D/Component/RenderComponent.hpp"

RenderComponent::RenderComponent(const sf::Texture& texture) : Component(RENDER) {
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(0, 0));
}

void RenderComponent::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}
