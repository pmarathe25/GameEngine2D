#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H
#include "System/System.hpp"

namespace StealthEngine {
    class MovementSystem : public System<MovementSystem> {
        public:
            virtual void update(float frametime) = 0;
    };
} /* StealthEngine */

#endif
