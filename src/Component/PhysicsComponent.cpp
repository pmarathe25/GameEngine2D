#include "GameEngine2D/Component/PhysicsComponent.hpp"

PhysicsComponent::PhysicsComponent(const sf::Vector2f& position, const sf::Vector2f& velocity) : Component(PHYSICS) {
    this -> position = position;
    this -> velocity = velocity;
}
