#include "GameEngine2D/Component/RenderComponent.hpp"

RenderComponent::RenderComponent(const sf::Texture& texture) {
    sprite.setTexture(texture);
}
