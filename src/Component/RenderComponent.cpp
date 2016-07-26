#include "GameEngine2D/Component/RenderComponent.hpp"

RenderComponent::RenderComponent(const sf::Texture& texture, const sf::Vector2f& position) : Component(RENDER) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
}
