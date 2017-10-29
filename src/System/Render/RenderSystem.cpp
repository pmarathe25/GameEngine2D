#include "System/Render/RenderSystem.hpp"

namespace StealthEngine {
    RenderSystem::RenderSystem(World& world, EventManager& eventManager, sf::RenderWindow& window)
        : System<RenderSystem>(world, eventManager), window(window) {
        std::function<void(int, const sf::Vector2f&)> callback = std::bind(&RenderSystem::onUpdatePosition, this, std::placeholders::_1, std::placeholders::_2);
        eventManager.request<EventManager::POSITION_CHANGED>(callback);
    }

    void RenderSystem::update(float frametime) {
        for (int i = 0; i < sprites.size(); ++i) {
            window.draw(sprites[i]);
        }
    }

    bool RenderSystem::addComponent(int eID, const sf::Texture& texture, const sf::Vector2f& position) {
        if (System<RenderSystem>::addComponent(eID, sprites, texture)) {
            sprites.back().setPosition(position);
        }
    }

    bool RenderSystem::removeComponent(int eID) {
        return System<RenderSystem>::removeComponent(eID, sprites);
    }

    sf::Sprite& RenderSystem::sprite(int eID) {
        return get(eID, sprites);
    }

    const sf::Sprite& RenderSystem::sprite(int eID) const {
        return get(eID, sprites);
    }

    void RenderSystem::onUpdatePosition(int eID, const sf::Vector2f& position) {
        if (hasEntity(eID)) {
            get(eID, sprites).setPosition(position);
        }
    }
} /* StealthEngine */
