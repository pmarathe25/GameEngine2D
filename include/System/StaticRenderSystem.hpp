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
            StaticRenderSystem(sf::RenderWindow& window) : window(window) { }
            void update(float frametime = 0);
            bool addComponent(int eID, const sf::Texture& texture, const sf::Vector2f& position = {});
            bool removeComponent(int eID);
            const sf::Sprite& getSprite(int eID) const;
        private:
            std::vector<sf::Sprite> sprites;
            sf::RenderWindow& window;
    };
} /* StealthEngine */

#endif
