#include "GameEngine2D/System/RenderSystem.hpp"

RenderSystem::RenderSystem(sf::RenderWindow* window, int expectedNumEntities) : System(expectedNumEntities) {
    this -> window = window;
}

int RenderComponent::addComponent(const ComponentType& newComponent, int eID, const sf::Vector2f& position) {
    int componentIndex System<RenderComponent>::addComponent(newComponent, eID);
    components[componentIndex].setPosition(position);
    return componentIndex;
}

void RenderSystem::update() {
    for (std::vector<RenderComponent>::iterator renderComponent = components.begin(); renderComponent != components.end(); ++renderComponent) {
        window -> draw(renderComponent -> sprite);
    }
}

void RenderSystem::syncComponent(int componentIndex, const sf::Vector2f& position) {
    components.at(componentIndex).sprite.setPosition(position);
}
