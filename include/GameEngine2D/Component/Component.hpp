#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
    public:
        Component();
        int getOwningEntityID() const;
        void setOwningEntityID(int eID);
    private:
        int eID;
};

#endif
