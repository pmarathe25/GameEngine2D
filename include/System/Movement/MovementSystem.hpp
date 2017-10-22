#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H
#include "System/System.hpp"
#include <math.h>

const float DIAGONALIZATION_FACTOR = 1 / (float) sqrt(2);

namespace StealthEngine {
    class MovementSystem : public System<MovementSystem> {
        public:
            virtual void update(float frametime) = 0;
    };
} /* StealthEngine */

#endif
