#ifndef COMPONENT_H
#define COMPONENT_H

enum componentID {
    RENDER = 0,
    PHYSICS
};

class Component {
    public:
        Component(componentID id);
        componentID cID;
        int eID;
};

#endif
