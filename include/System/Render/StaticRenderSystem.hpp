#ifndef STATIC_RENDER_SYSTEM_H
#define STATIC_RENDER_SYSTEM_H
#include "System/System.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

namespace StealthEngine {
    class StaticRenderSystem : public System<StaticRenderSystem> {
        public:
            StaticRenderSystem(World& world, EventManager& eventManager, sf::RenderWindow& window) : System<StaticRenderSystem>(world, eventManager), window(window) { }
            void update(float frametime);
            bool addComponent(int eID, const sf::Texture& texture, const sf::Vector2f& position = {});
            bool removeComponent(int eID);
            sf::Sprite& sprite(int eID);
            // Constant accessors
            const sf::Sprite& sprite(int eID) const;
        protected:
            std::vector<sf::Sprite> sprites;
            sf::RenderWindow& window;
    };
} /* StealthEngine */

#endif
