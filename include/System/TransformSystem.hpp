#ifndef TRANSFORM_SYSTEM_H
#define TRANSFORM_SYSTEM_H
#include "System/System.hpp"
#include <SFML/System.hpp>
#include <vector>

namespace StealthEngine {
    class TransformSystem : public System<TransformSystem> {
        public:
            TransformSystem() { }
            void update(float frametime = 0);
            bool addComponent(int eID, sf::Vector2f position = {}, float rotation = 0, sf::Vector2f scale = {});
            bool removeComponent(int eID);
            sf::Vector2f& position(int eID);
            float& rotation(int eID);
            sf::Vector2f& scale(int eID);
            // Constant accessors.
            const sf::Vector2f& position(int eID) const;
            float rotation(int eID) const;
            const sf::Vector2f& scale(int eID) const;
        private:
            std::vector<sf::Vector2f> positions;
            std::vector<float> rotations;
            std::vector<sf::Vector2f> scales;
    };
} /* StealthEngine */

#endif
