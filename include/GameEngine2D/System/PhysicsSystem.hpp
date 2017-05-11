#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H
#include "GameEngine2D/System/System.hpp"
#include "GameEngine2D/Component/PhysicsComponent.hpp"
#include "GameEngine2D/SubscriberQueue.hpp"
#include <vector>
#include <utility>
#include <deque>

class PhysicsSystem : public System<PhysicsComponent> {
    public:
        PhysicsSystem(int systemID, EntityManager& entityManager);
        bool addComponent(int eID, const PhysicsComponent& newComponent);
        SubscriberQueue<std::deque<int> >& getComponentAddedQueue();
        void update(float frametime);
    private:
        SubscriberQueue<std::deque<int> > componentAddedQueue;
};

#endif
