#include "GameEngine2D/System/RenderSystem.hpp"

RenderSystem::RenderSystem(int systemID, EntityManager& entityManager, sf::RenderWindow* window, PhysicsSystem* physicsSystem) : System<RenderComponent>(entityManager, systemID) {
    this -> window = window;
    this -> physicsSystem = physicsSystem;
    if (physicsSystem != NULL) {
        physicsSystem -> getComponentQueue().registerSubscriber(getSystemID());
    }
}

bool RenderSystem::addComponent(int eID, const RenderComponent& newComponent) {
    System<RenderComponent>::addComponent(eID, newComponent);
    if (physicsSystem != NULL) {
        PhysicsComponent* temp = physicsSystem -> getComponentByEntityID(eID);
        if (temp != NULL) {
            components.back().bHasPhysics = true;
        }
    }
}

void RenderSystem::update(float frametime) {
    // Check the physics queue
    if (physicsSystem != NULL) {
        int queueSize =  physicsSystem -> getComponentQueue().size();
        if (queueSize != 0) {
            for (int i = 0; i < queueSize; ++i) {
                RenderComponent* temp = getComponentByEntityID(physicsSystem -> getComponentQueue()[i]);
                if (temp != NULL) {
                    temp -> bHasPhysics = physicsSystem -> getComponentByEntityID(physicsSystem -> getComponentQueue()[i]) != NULL;
                }
            }
            physicsSystem -> getComponentQueue().done(getSystemID());
        }
    }
    // Then update and draw the components.
    for (std::vector<RenderComponent>::iterator renderComponent = components.begin(); renderComponent != components.end(); ++renderComponent) {
        if (physicsSystem != NULL && renderComponent -> bHasPhysics) {
            renderComponent -> sprite.setPosition(physicsSystem -> getComponentByMatchingComponent(*renderComponent) -> position);
        }
        if (!isOffScreen(renderComponent -> sprite.getPosition(), renderComponent -> sprite.getTexture() -> getSize())) {
            window -> draw(renderComponent -> sprite);
        }
    }
}

bool RenderSystem::isOffScreen(const sf::Vector2f& position, const sf::Vector2u& size) {
    return position.x + size.x < 0 || position.x >  window -> getSize().x || position.y + size.y < 0 || position.y >  window -> getSize().y;
}
