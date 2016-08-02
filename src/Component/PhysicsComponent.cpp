#include "GameEngine2D/Component/PhysicsComponent.hpp"

PhysicsComponent::PhysicsComponent(const sf::Vector2f& velocity) : Component(PHYSICS) {
    this -> velocity = velocity;
}
