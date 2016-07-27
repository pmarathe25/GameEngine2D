#include "GameEngine2D/System/RenderSystem.hpp"

RenderSystem::RenderSystem(sf::RenderWindow* window, int expectedNumEntities) : System() {
    this -> window = window;
    renderComponents.reserve(expectedNumEntities);
}

void RenderSystem::update() {
    for (std::vector<RenderComponent>::iterator renderComponent = renderComponents.begin(); renderComponent != renderComponents.end(); ++renderComponent) {
        window -> draw(renderComponent -> sprite);
    }
}

Component* RenderSystem::addComponent(const RenderComponent& newComponent) {
    renderComponents.push_back(newComponent);
    return &renderComponents.back();
}
