#ifndef COMPONENT_H
#define COMPONENT_H

enum componentID {
    RENDER
};

class Component {
    public:
        Component(componentID id);
        componentID cID;
        int eID;
};

#endif
