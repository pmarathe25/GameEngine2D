#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H
#include "GameEngine2D/System/System.hpp"
#include "GameEngine2D/Component/RenderComponent.hpp"
#include <vector>
#include <SFML/Window.hpp>

class RenderSystem : public System<RenderComponent> {
    public:
        RenderSystem(sf::RenderWindow* window, int expectedNumEntities);
        void update();
    private:
        sf::RenderWindow* window;
};

#endif
