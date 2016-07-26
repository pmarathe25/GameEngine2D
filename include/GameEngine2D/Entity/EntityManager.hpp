#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "GameEngine2D/Entity/Entity.hpp"
#include "GameEngine2D/Component/Component.hpp"
#include <SFML/Window.hpp>
#include <vector>
#include <deque>

class EntityManager {
    public:
        EntityManager(sf::RenderWindow* window, int expectedNumEntities = 10);
        int getNewEntity(const sf::Vector2f& position);
        void destroyEntity(int eID);
        void update(float frametime);
        void attachComponent(int eID, const Component& component);
        void detachComponent(int eID, componentID cID);
    private:
        std::vector<Entity> entities;
        std::deque<int> freeIDs;
        RenderSystem renderModule;
};

#endif
