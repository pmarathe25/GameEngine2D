#include "GameEngine2D/System/RenderSystem.hpp"

RenderSystem::RenderSystem(int systemID, EntityManager& entityManager, sf::RenderWindow* window, PhysicsSystem* physicsSystem) : System<RenderComponent>(entityManager, systemID) {
    this -> window = window;
    this -> physicsSystem = physicsSystem;
    physicsSystem -> getComponentQueue().registerSubscriber(getSystemID());
}

bool RenderSystem::addComponent(int eID, const RenderComponent& newComponent) {
    System<RenderComponent>::addComponent(eID, newComponent);
    PhysicsComponent* temp = physicsSystem -> getComponentByEntityID(eID);
    if (temp != NULL) {
        components.back().bHasPhysics = true;
    }
}

void RenderSystem::update(float frametime) {
    // Check the physics queue
    if (physicsSystem -> getComponentQueue().size() != 0) {
        int queueSize =  physicsSystem -> getComponentQueue().size();
        for (int i = 0; i < queueSize; ++i) {
            RenderComponent* temp = getComponentByEntityID(physicsSystem -> getComponentQueue()[i]);
            if (temp != NULL) {
                temp -> bHasPhysics = physicsSystem -> getComponentByEntityID(physicsSystem -> getComponentQueue()[i]) != NULL;
            }
        }
        physicsSystem -> getComponentQueue().clear(getSystemID());
    }
    // Now update the components.
    for (std::vector<RenderComponent>::iterator renderComponent = components.begin(); renderComponent != components.end(); ++renderComponent) {
        if (physicsSystem != 0) {
            if (renderComponent -> bHasPhysics) {
                renderComponent -> sprite.setPosition(physicsSystem -> getComponentByMatchingComponent(*renderComponent) -> position);
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
