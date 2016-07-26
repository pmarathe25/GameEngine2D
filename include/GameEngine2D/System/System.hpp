#ifndef SYSTEM_H
#define SYSTEM_H

class System {
    public:
        System();
        virtual void update(float frametime) = 0;
        virtual Component* addComponent() = 0;
};

#endif
