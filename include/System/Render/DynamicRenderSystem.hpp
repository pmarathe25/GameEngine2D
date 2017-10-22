#ifndef DYNAMIC_RENDER_SYSTEM_H
#define DYNAMIC_RENDER_SYSTEM_H
#include "System/Render/StaticRenderSystem.hpp"
#include "System/TransformSystem.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

namespace StealthEngine {
    class DynamicRenderSystem : public StaticRenderSystem {
        public:
            DynamicRenderSystem(sf::RenderWindow& window, const TransformSystem& transformSystem) : StaticRenderSystem(window), transformSystem(transformSystem) { }
            void update(float frametime);
            bool addComponent(int eID, const sf::Texture& texture);
        private:
            const TransformSystem& transformSystem;
    };
} /* StealthEngine */

#endif
