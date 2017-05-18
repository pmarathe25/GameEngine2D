#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H
#include "GameEngine2D/System/System.hpp"
#include "GameEngine2D/Component/CollisionComponent.hpp"
#include "GameEngine2D/SubscriberQueue.hpp"
#include <vector>


class CollisionSystem : public System<CollisionComponent> {
    public:
        CollisionSystem(int systemID, EntityManager& entityManager, PhysicsSystem* physicsSystem = NULL);
        bool addComponent(int eID, const CollisionComponent& newComponent);
        void update(float frametime);
    private:
        // TODO: Create collision events of some manner.
        // SubscriberQueue<std::vector<CollisionEvent> > collisions;
        // TODO: Create a 2D structure to hold indexes of collision components. Each grid block will have an unordered_map of eID -> CollisionComponent.
        // TileMap<int> collisionComponents;

};

#endif
