#include "GameEngine2D/System/RenderSystem.hpp"

RenderSystem::RenderSystem(sf::RenderWindow* window, int expectedNumEntities) : System(expectedNumEntities) {
    this -> window = window;
}

void RenderSystem::update() {
    for (std::vector<RenderComponent>::iterator renderComponent = components.begin(); renderComponent != components.end(); ++renderComponent) {
        window -> draw(renderComponent -> sprite);
    }
}

void RenderSystem::syncComponent(int componentIndex, const sf::Vector2f& position) {
    components.at(componentIndex).sprite.setPosition(position);
}
