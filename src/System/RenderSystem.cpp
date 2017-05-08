#include "GameEngine2D/System/RenderSystem.hpp"

RenderSystem::RenderSystem(int systemID, EntityManager& entityManager, sf::RenderWindow* window, PhysicsSystem* physicsSystem) : System<RenderComponent>(entityManager, systemID) {
    this -> window = window;
    this -> physicsSystem = physicsSystem;
}

void RenderSystem::update(float frametime) {
    for (std::vector<RenderComponent>::iterator renderComponent = components.begin(); renderComponent != components.end(); ++renderComponent) {
        if (physicsSystem != 0) {
            PhysicsComponent* temp = physicsSystem -> getComponentByMatchingComponent(*renderComponent);
            if (temp != NULL) {
                renderComponent -> sprite.setPosition(temp -> position);
            }
        }
        if (!isOffScreen(renderComponent -> sprite.getPosition(), renderComponent -> sprite.getTexture() -> getSize())) {
            window -> draw(renderComponent -> sprite);
        }
    }
}

bool RenderSystem::isOffScreen(const sf::Vector2f& position, const sf::Vector2u& size) {
    return position.x + size.x < 0 || position.x >  window -> getSize().x || position.y + size.y < 0 || position.y >  window -> getSize().y;
}
