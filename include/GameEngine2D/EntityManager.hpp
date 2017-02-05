#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "GameEngine2D/Entity/Entity.hpp"
#include "GameEngine2D/Component/Component.hpp"
#include "GameEngine2D/System/RenderSystem.hpp"
#include "GameEngine2D/System/PhysicsSystem.hpp"
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
        // Attach a component of any kind. Return whether it was successfully attached.
        bool attachComponent(int eID, const Component& component);
        // Remove any kind of component. Return whether it was successfully detached.
        bool detachComponent(int eID, componentID cID);
        // Entity getters.
        Entity& getEntity(int eID);
        Entity& getOwningEntity(const Component& component);
        Entity& getOwningEntity(const Component* component);
    private:
        std::vector<Entity> entities;
        std::deque<int> freeIDs;
        RenderSystem renderSystem;
        PhysicsSystem physicsSystem;
        void updateEntity(int eID, componentID cID, int componentIndex);
        void sync();
};

#endif
