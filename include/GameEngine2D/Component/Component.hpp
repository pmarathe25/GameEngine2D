#ifndef COMPONENT_H
#define COMPONENT_H

enum componentID {
    RENDER = 0,
    PHYSICS
};

class Component {
    public:
        Component(componentID id);
        int getComponentID() const;
        int getOwningEntityID() const;
        void setOwningEntityID(int eID);
    private:
        componentID cID;
        int eID;
};

#endif
