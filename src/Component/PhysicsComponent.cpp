#include "GameEngine2D/Component/PhysicsComponent.hpp"

PhysicsComponent::PhysicsComponent(const sf::Vector2f& velocity) : Component(PHYSICS) {
    this -> velocity = velocity;
}

void PhysicsComponent::setPosition(const sf::Vector2f& position) {
    this -> position = position;
}
