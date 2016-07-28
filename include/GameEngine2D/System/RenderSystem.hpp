#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H
#include "GameEngine2D/System/System.hpp"
#include "GameEngine2D/Component/RenderComponent.hpp"
#include <vector>
#include <SFML/Window.hpp>

class RenderSystem : public System {
    public:
        RenderSystem(EntityManager* entityManager, sf::RenderWindow* window, int expectedNumEntities);
        void update();
        std::pair<Component*, int> addComponent(const RenderComponent& newComponent);
        void removeComponent(int index);
    private:
        std::vector<RenderComponent> renderComponents;
        sf::RenderWindow* window;
};

#endif
