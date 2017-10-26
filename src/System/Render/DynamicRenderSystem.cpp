#include "System/Render/DynamicRenderSystem.hpp"

namespace StealthEngine {
    DynamicRenderSystem::DynamicRenderSystem(World& world, EventManager& eventManager, sf::RenderWindow& window)
        : StaticRenderSystem(world, eventManager, window) {
        std::function<void(int, const sf::Vector2f&)> callback = std::bind(&DynamicRenderSystem::onUpdatePosition, this, std::placeholders::_1, std::placeholders::_2);
        eventManager.request<EventManager::POSITION_CHANGED>(callback);
    }

    void DynamicRenderSystem::update(float frametime) {
        for (int i = 0; i < sprites.size(); ++i) {
            // Update positions before drawing.
            // int eID = componentEntity[i];
            // try {
            //     // sprites[i].setPosition(transformSystem.position(eID));
            // } catch (std::invalid_argument& e) {
            //     throw std::invalid_argument("DynamicRenderSystem cannot update entities with no Transform component.");
            // }
            window.draw(sprites[i]);
        }
    }

    bool DynamicRenderSystem::addComponent(int eID, const sf::Texture& texture) {
        return StaticRenderSystem::addComponent(eID, texture);
    }

    void DynamicRenderSystem::onUpdatePosition(int eID, const sf::Vector2f& position) {
        StaticRenderSystem::get(eID, sprites).setPosition(position);
    }
} /* StealthEngine */
