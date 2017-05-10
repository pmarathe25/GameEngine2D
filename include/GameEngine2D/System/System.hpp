#ifndef SYSTEM_H
#define SYSTEM_H
#include "GameEngine2D/Component/Component.hpp"
#include "GameEngine2D/Entity/EntityManager.hpp"
#include <vector>

class SystemParent {
    virtual int getSystemID() = 0;
    virtual void update(float frametime) = 0;
};

template <class ComponentType>
class System : public SystemParent {
    public:
        System(EntityManager& entityManager, int systemID) {
            this -> entityManager = &entityManager;
            this -> systemID = systemID;
        }

        // Add a component to the system and returns a pointer to it and index (to register it with the entity).
        void addComponent(int eID, const ComponentType& newComponent) {
            if (entityManager -> getEntity(eID).registerComponent(getSystemID(), components.size())) {
                components.push_back(newComponent);
                components.back().setOwningEntityID(eID);
            }
        }

        // Remove a component from the system and returns the eID of the owning entity of the other modified component.
        void removeComponent(int eid, bool entityDestroyed = false) {
            // Return the index of the other entity that was modified.
            Entity* entity = &(entityManager -> getEntity(eid));
            int componentIndex = entity -> getComponentIndexByID(getSystemID());
            if (componentIndex != -1) {
                if (!entityDestroyed) {
                    // First remove the component from the entity if the entity is not being destroyed.
                    entity -> deregisterComponent(getSystemID());
                }
                // Swap the component to remove with the last component and update the entity of the swapped component.
                components[componentIndex] = components.back();
                components.pop_back();
                entityManager -> getEntity(components[componentIndex]).updateCommponent(getSystemID(), componentIndex);
            }
        }

        // Get a reference to a component.
        ComponentType* getComponent(int index) {
            return &components[index];
        }

        // Get a reference to a component by its owning entity id.
        ComponentType* getComponentByOwningEntityID(int eid) {
            int index = entityManager -> getEntity(eid).getComponentIndexByID(getSystemID());
            if (index != -1) {
                return &components[index];
            } else {
                return NULL;
            }
        }

        ComponentType* getComponentByMatchingComponent(Component& component) {
            int index = entityManager -> getEntity(component).getComponentIndexByID(getSystemID());
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
