#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "GameEngine2D/Entity/Entity.hpp"
#include "GameEngine2D/Component/Component.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <vector>
#include <deque>

class System;

class EntityManager {
    public:
        EntityManager();
        int createEntity();
        void destroyEntity(int eID);
        void update(float frametime);
        // Entity getters.
        Entity& getEntity(int eID);
        Entity& getOwningEntity(const Component& component);
        Entity& getOwningEntity(const Component* component);
    private:
        std::vector<Entity> entities;
        std::map<int, std::vector<System*> > systems;
        std::deque<int> freeIDs;
        void updateEntity(int eID, std::string cID, int componentIndex);
        void sync();
};

#endif
