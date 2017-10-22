#include "System/StaticRenderSystem.hpp"

namespace StealthEngine {
    void StaticRenderSystem::update(float frametime) {
        for (int i = 0; i < sprites.size(); ++i) {
            window.draw(sprites[i]);
        }
    }

    bool StaticRenderSystem::addComponent(int eID, const sf::Texture& texture, const sf::Vector2f& position) {
        if (System<StaticRenderSystem>::addComponent(eID)) {
            sprites.emplace_back(texture);
            sprites.back().setPosition(position);
        }
    }

    bool StaticRenderSystem::removeComponent(int eID) {
        return System<StaticRenderSystem>::removeComponent(eID);
    }

    const sf::Sprite& StaticRenderSystem::getSprite(int eID) {
        return sprites[eID];
    }
} /* StealthEngine */
