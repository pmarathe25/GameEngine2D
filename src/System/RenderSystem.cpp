#include "GameEngine2D/System/RenderSystem.hpp"

RenderSystem::RenderSystem(sf::RenderWindow* window) {
    this -> window = window;
}

void RenderSystem::update() {
    for (std::vector<RenderComponent>::iterator component = components.begin(); component != components.end(); ++component) {
        window -> draw(component -> sprite);
    }
}

Component* RenderSystem::addComponent(const RendeComponent& newComponent) {
    components.push_back(newComponent);
    return &components.back();
}
