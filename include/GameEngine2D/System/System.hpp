#ifndef SYSTEM_H
#define SYSTEM_H
#include <utility>

class EntityManager;

class System {
    public:
        System(EntityManager* entityManager);
        virtual void update() = 0;
    protected:
        EntityManager* entityManager;
};

#endif
