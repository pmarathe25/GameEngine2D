#include "GameEngine2D/System/RenderSystem.hpp"
#include "GameEngine2D/EntityManager.hpp"

RenderSystem::RenderSystem(EntityManager* entityManager, sf::RenderWindow* window, int expectedNumEntities) : System(entityManager) {
    this -> window = window;
    renderComponents.reserve(expectedNumEntities);
}

void RenderSystem::update() {
    for (std::vector<RenderComponent>::iterator renderComponent = renderComponents.begin(); renderComponent != renderComponents.end(); ++renderComponent) {
        window -> draw(renderComponent -> sprite);
    }
}

std::pair<Component*, int> RenderSystem::addComponent(const RenderComponent& newComponent) {
    if (renderComponents.size() + 1 >= renderComponents.capacity()) {
        renderComponents.reserve(renderComponents.capacity() * 2);
    }
    renderComponents.push_back(newComponent);
    return std::make_pair(&renderComponents.back(), renderComponents.size() - 1);
}

void RenderSystem::removeComponent(int index) {
    // Swap the component to remove with the last component.
    renderComponents.at(index) = renderComponents.back();
    // Update the entity.
    entityManager -> getOwningEntity(renderComponents.back()).updateCommponent(RENDER, index);
    // Pop.
    renderComponents.pop_back();
}
