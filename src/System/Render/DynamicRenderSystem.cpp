#include "System/Render/DynamicRenderSystem.hpp"

namespace StealthEngine {
    DynamicRenderSystem::DynamicRenderSystem(World& world, EventManager& eventManager, sf::RenderWindow& window)
        : StaticRenderSystem(world, eventManager, window) {
        std::function<void(int, const sf::Vector2f&)> callback = std::bind(&DynamicRenderSystem::onUpdatePosition, this, std::placeholders::_1, std::placeholders::_2);
        eventManager.request<EventManager::POSITION_CHANGED>(callback);
    }

    void DynamicRenderSystem::update(float frametime) {
        for (int i = 0; i < sprites.size(); ++i) {
            window.draw(sprites[i]);
        }
    }

    bool DynamicRenderSystem::addComponent(int eID, const sf::Texture& texture) {
        return StaticRenderSystem::addComponent(eID, texture);
    }

    void DynamicRenderSystem::onUpdatePosition(int eID, const sf::Vector2f& position) {
        if (hasEntity(eID)) {
            get(eID, sprites).setPosition(position);
        }
    }
} /* StealthEngine */
