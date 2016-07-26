#ifndef SYSTEM_H
#define SYSTEM_H
#include "GameEngine2D/Component/Component.hpp"

class System {
    public:
        System();
        virtual void update() = 0;
        virtual Component* addComponent(const Component& newComponent) = 0;
};

#endif
