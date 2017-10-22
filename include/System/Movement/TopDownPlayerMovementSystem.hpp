#ifndef TOP_DOWN_PLAYER_MOVEMENT_SYSTEM_H
#define TOP_DOWN_PLAYER_MOVEMENT_SYSTEM_H
#include "System/Movement/PlayerMovementSystem.hpp"

namespace StealthEngine {
    class TopDownPlayerMovementSystem : public PlayerMovementSystem {
        public:
            TopDownPlayerMovementSystem(std::map<Intent, sf::Keyboard::Key> keymap, TransformSystem& transformSystem) : PlayerMovementSystem(keymap, transformSystem) { }
            void update(float frametime);
    };
} /* StealthEngine */

#endif
