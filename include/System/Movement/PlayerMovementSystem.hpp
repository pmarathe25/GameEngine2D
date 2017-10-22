#ifndef PLAYER_MOVEMENT_SYSTEM_H
#define PLAYER_MOVEMENT_SYSTEM_H
#include "System/Movement/MovementSystem.hpp"
#include <SFML/Window.hpp>
#include <map>

namespace StealthEngine {
    enum Intent {
        MOVE_UP = 0,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        JUMP,
    };

    class PlayerMovementSystem : public MovementSystem {
        public:
            virtual void update(float frametime = 0) = 0;
            float& movementSpeed(int eID);
            float movementSpeed(int eID) const;
        protected:
            std::map<Intent, sf::Keyboard::Key> map;
            std::vector<float> movementSpeeds;
    };
} /* StealthEngine */


#endif
