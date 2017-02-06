#include "GameEngine2D/Component/RenderComponent.hpp"

RenderComponent::RenderComponent(const sf::Texture& texture) : Component(RENDER) {
    sprite.setTexture(texture);
}
