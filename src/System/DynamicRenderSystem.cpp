#include "System/DynamicRenderSystem.hpp"

namespace StealthEngine {
    void DynamicRenderSystem::update(float frametime) {
        for (int i = 0; i < sprites.size(); ++i) {
            // Update positions before drawing.
            int eID = componentEntity[i];
            try {
                sprites[i].setPosition(transformSystem.position(eID));
            } catch (std::invalid_argument& e) {
                throw std::invalid_argument("DynamicRenderSystem cannot update entities with no Transform component.");
            }
            window.draw(sprites[i]);
        }
    }

    bool DynamicRenderSystem::addComponent(int eID, const sf::Texture& texture) {
        if (!transformSystem.hasEntity(eID)) {
            throw std::invalid_argument("Cannot add Dynamic Render Component to an Entity with no Transform component.");
        }
        return StaticRenderSystem::addComponent(eID, texture);
    }
} /* StealthEngine */
