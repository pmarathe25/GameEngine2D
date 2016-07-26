#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H
#include "GameEngine2D/System/System.hpp"
#include "GameEngine2D/Component/RenderComponent.hpp"
#include <vector>
#include <SFML/Window.hpp>

class RenderSystem : public System {
    public:
        RenderSystem();
        virtual void update();
        virtual Component* addComponent(const RenderComponent& newComponent);
    private:
        std::vector<RenderComponent> components;
        sf::RenderWindow* window;
};

#endif
