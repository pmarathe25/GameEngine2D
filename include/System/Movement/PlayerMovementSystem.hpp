#ifndef PLAYER_MOVEMENT_SYSTEM_H
#define PLAYER_MOVEMENT_SYSTEM_H
#include "System/TransformSystem.hpp"
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
            PlayerMovementSystem(std::map<Intent, sf::Keyboard::Key> keymap, TransformSystem& transformSystem) : transformSystem(transformSystem), keymap(keymap) { }
            virtual void update(float frametime) = 0;
            bool addComponent(int eID, float movementSpeed);
            bool removeComponent(int eID);
            float& movementSpeed(int eID);
            float movementSpeed(int eID) const;
        protected:
            TransformSystem& transformSystem;
            std::map<Intent, sf::Keyboard::Key> keymap;
            std::vector<float> movementSpeeds;
    };
} /* StealthEngine */


#endif
