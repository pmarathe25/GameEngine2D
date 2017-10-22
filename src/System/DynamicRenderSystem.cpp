#include "System/DynamicRenderSystem.hpp"

namespace StealthEngine {
    void DynamicRenderSystem::update(float frametime) {
        for (int i = 0; i < sprites.size(); ++i) {
            // Update positions before drawing.
            int eID = componentEntity[i];
            sprites[i].setPosition(transformSystem.hasEntity(eID) ? transformSystem.position(eID) : sprites[i].getPosition());
            window.draw(sprites[i]);
        }
    }
} /* StealthEngine */
