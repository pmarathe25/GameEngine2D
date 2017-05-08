#include "GameEngine2D/Component/RenderComponent.hpp"

RenderComponent::RenderComponent(const sf::Texture& texture, const sf::Vector2f& position) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
}
