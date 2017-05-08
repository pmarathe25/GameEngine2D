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

class EntityManager {
    public:
        EntityManager();
        int createEntity();
        void destroyEntity(int eID);
        // Entity getters.
        Entity& getEntity(int eID);
        Entity& getEntity(const Component& component);
        Entity& getEntity(const Component* component);
    private:
        std::vector<Entity> entities;
        std::deque<int> freeIDs;
        void updateEntity(int eID, std::string cID, int componentIndex);
};

#endif
