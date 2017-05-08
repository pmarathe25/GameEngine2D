#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H
#include "GameEngine2D/System/SystemType.hpp"
#include "GameEngine2D/Component/PhysicsComponent.hpp"
#include <vector>
#include <utility>

class PhysicsSystem : public SystemType<PhysicsComponent> {
    public:
        PhysicsSystem(int systemID, EntityManager& entityManager);
        void update(float frametime);
};

#endif
