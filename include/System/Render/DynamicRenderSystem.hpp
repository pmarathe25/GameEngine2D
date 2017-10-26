#ifndef DYNAMIC_RENDER_SYSTEM_H
#define DYNAMIC_RENDER_SYSTEM_H
#include "System/Render/StaticRenderSystem.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

namespace StealthEngine {
    class DynamicRenderSystem : public StaticRenderSystem {
        public:
            DynamicRenderSystem(World& world, EventManager& eventManager, sf::RenderWindow& window);
            void update(float frametime);
            bool addComponent(int eID, const sf::Texture& texture);
            // Callback for eventManager
            void onUpdatePosition(int eID, const sf::Vector2f& position);
        private:
    };
} /* StealthEngine */

#endif
