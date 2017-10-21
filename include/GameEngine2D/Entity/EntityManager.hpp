#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "GameEngine2D/Entity/Entity.hpp"
#include "GameEngine2D/Component/Component.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <vector>
#include <list>

class SystemBase;

class EntityManager {
    public:
        EntityManager();
        int createEntity();
        void destroyEntity(int eID);
        void registerSystems(std::vector<SystemBase*> unregisteredSystems);
        Entity* getEntity(int eID);
        Entity* getEntity(const Component& component);
        Entity* getEntity(const Component* component);
        int size();
    private:
        std::vector<Entity> entities;
        std::list<int> freeIDs;
        std::unordered_map <int, SystemBase*> systems;
        void updateEntity(int eID, std::string cID, int componentIndex);
};

#endif
