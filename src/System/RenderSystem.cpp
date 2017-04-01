#include "GameEngine2D/System/RenderSystem.hpp"

RenderSystem::RenderSystem(EntityManager& entityManager, sf::RenderWindow* window, PhysicsSystem* physicsSystem) : SystemType<RenderComponent>(entityManager) {
    this -> window = window;
    this -> physicsSystem = physicsSystem;
    systemType = 1;
}

void RenderSystem::update(float frametime) {
    for (std::vector<RenderComponent>::iterator renderComponent = components.begin(); renderComponent != components.end(); ++renderComponent) {
        if (physicsSystem != 0) {
            renderComponent -> sprite.setPosition(physicsSystem -> getComponentByOwningEntityID(renderComponent -> getOwningEntityID()).position);
        }
        if (!isOffScreen(renderComponent -> sprite.getPosition(), renderComponent -> sprite.getTexture() -> getSize())) {
            window -> draw(renderComponent -> sprite);
        }
    }
}

int RenderSystem::getSystemType() {
    return systemType;
}

bool RenderSystem::isOffScreen(const sf::Vector2f& position, const sf::Vector2u& size) {
    return position.x + size.x < 0 || position.x >  window -> getSize().x || position.y + size.y < 0 || position.y >  window -> getSize().y;
}
