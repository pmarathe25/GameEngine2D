#include "GameEngine2D/Component/CollisionComponent.hpp"

CollisionComponent::CollisionComponent(const sf::Vector2f& boundingBox, const sf::Vector2f& position) {
    this -> boundingBox = boundingBox;
    this -> position = position;
}
