#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H
#include "GameEngine2D/System/System.hpp"
#include "GameEngine2D/Component/PhysicsComponent.hpp"
#include "GameEngine2D/SubscriberQueue.hpp"
#include <deque>

class PhysicsSystem : public System<PhysicsComponent> {
    public:
        PhysicsSystem(int systemID, EntityManager& entityManager);
        bool addComponent(int eID, const PhysicsComponent& newComponent);
        int removeComponentByEntityID(int eID);
        int removeComponentByIndex(int componentIndex, bool entityDestroyed = false);
        SubscriberQueue<std::deque<int> >& getComponentQueue();
        void update(float frametime);
    private:
        SubscriberQueue<std::deque<int> > componentQueue;
};

#endif
