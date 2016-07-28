#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "GameEngine2D/Entity/Entity.hpp"
#include "GameEngine2D/Component/Component.hpp"
#include "GameEngine2D/System/RenderSystem.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>

class EntityManager {
    public:
        EntityManager(sf::RenderWindow* window, int expectedNumEntities = 10);
        int createEntity(const sf::Vector2f& position = sf::Vector2f(0, 0));
        void destroyEntity(int eID);
        void update(float frametime);
        void attachComponent(int eID, const RenderComponent& component);
        // Remove any kind of component.
        void detachComponent(int eID, componentID cID);
        Entity& getEntity(int eID);
        Entity& getOwningEntity(const Component& component);
    private:
        std::vector<Entity> entities;
        std::deque<int> freeIDs;
        RenderSystem renderSystem;
};

#endif
