#ifndef SYSTEM_H
#define SYSTEM_H
#include "GameEngine2D/Component/Component.hpp"
#include "GameEngine2D/Entity/EntityManager.hpp"
#include <vector>
#include <deque>

class SystemParent {
    public:
        virtual int getSystemID() = 0;
        virtual void update(float frametime) = 0;
        virtual void removeComponentByEntityID(int eID) = 0;
        virtual void removeComponentByIndex(int componentIndex, bool entityDestroyed) = 0;
};

template <class ComponentType>
class System : public SystemParent {
    public:
        System(EntityManager& entityManager, int systemID) {
            this -> entityManager = &entityManager;
            this -> systemID = systemID;
        }

        // Add a component to the system if the entity does not have one from this system already.
        void addComponent(int eID, const ComponentType& newComponent) {
            if (entityManager -> getEntity(eID) -> registerComponent(getSystemID(), components.size())) {
                components.push_back(newComponent);
                components.back().setOwningEntityID(eID);
            }
        }

        // Remove a component from the system and returns the eID of the owning entity of the other modified component.
        void removeComponentByEntityID(int eID) {
            // Return the index of the other entity that was modified.
            Entity* entity = entityManager -> getEntity(eID);
            int componentIndex = entity -> getComponentIndexByID(getSystemID());
            if (componentIndex != -1) {
                // First remove the component from the entity.
                entity -> deregisterComponent(getSystemID());
                if (componentIndex != size() - 1 && size() > 1) {
                    // Swap the component to remove with the last component and update the entity of the swapped component.
                    components[componentIndex] = components.back();
                    entityManager -> getEntity(components[componentIndex]) -> updateCommponent(getSystemID(), componentIndex);
                }
                components.pop_back();
            }
        }

        void removeComponentByIndex(int componentIndex, bool entityDestroyed = false) {
            // Return the index of the other entity that was modified.
            if (componentIndex != -1) {
                if (!entityDestroyed) {
                    // First remove the component from the entity if the entity is not being destroyed.
                    entityManager -> getEntity(components[componentIndex]) -> deregisterComponent(getSystemID());
                }
                if (componentIndex != size() - 1 && size() > 1) {
                    // Swap the component to remove with the last component and update the entity of the swapped component.
                    components[componentIndex] = components.back();
                    entityManager -> getEntity(components[componentIndex]) -> updateCommponent(getSystemID(), componentIndex);
                }
                components.pop_back();
            }
        }

        // Get a reference to a component.
        ComponentType* getComponent(int index) {
            return &components[index];
        }

        // Get a reference to a component by its owning entity id.
        ComponentType* getComponentByOwningEntityID(int eID) {
            int index = entityManager -> getEntity(eID) -> getComponentIndexByID(getSystemID());
            if (index != -1) {
                return &components[index];
            } else {
                return NULL;
            }
        }

        ComponentType* getComponentByMatchingComponent(Component& component) {
            int index = entityManager -> getEntity(component) -> getComponentIndexByID(getSystemID());
            if (index != -1) {
                return &components[index];
            } else {
                return NULL;
            }
        }

        int size() {
            return components.size();
        }

        int getSystemID() {
            return systemID;
        };

        virtual void update(float frametime) = 0;
    protected:
        std::vector<ComponentType> components;
        EntityManager* entityManager;
        int systemID;
};

#endif
