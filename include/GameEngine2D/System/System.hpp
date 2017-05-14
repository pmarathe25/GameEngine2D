#ifndef SYSTEM_H
#define SYSTEM_H
#include "GameEngine2D/Component/Component.hpp"
#include "GameEngine2D/Entity/EntityManager.hpp"
#include <vector>

class SystemParent {
    public:        
        int getSystemID() {
            return systemID;
        }

        virtual void update(float frametime) = 0;
        virtual int removeComponentByEntityID(int eID) = 0;
        virtual int removeComponentByIndex(int componentIndex, bool entityDestroyed) = 0;
    protected:
        int systemID;
};

template <class ComponentType>
class System : public SystemParent {
    public:
        System(EntityManager& entityManager, int systemID) {
            this -> entityManager = &entityManager;
            this -> systemID = systemID;
        }

        // Add a component to the system if the entity does not have one from this system already.
        bool addComponent(int eID, const ComponentType& newComponent) {
            if (entityManager -> getEntity(eID) -> registerComponent(getSystemID(), components.size())) {
                components.push_back(newComponent);
                components.back().setOwningEntityID(eID);
                return true;
            }
            return false;
        }

        // Remove a component from the system and returns the eID of the owning entity of the other modified component.
        int removeComponentByEntityID(int eID) {
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
                    components.pop_back();
                    return components[componentIndex].getOwningEntityID();
                } else {
                    components.pop_back();
                    return eID;
                }
            } else {
                return -1;
            }
        }

        int removeComponentByIndex(int componentIndex, bool entityDestroyed = false) {
            if (componentIndex < 0 || componentIndex >= size()) {
                return -1;
            } else {
                // Return the index of the other entity that was modified.
                if (!entityDestroyed) {
                    // First remove the component from the entity if the entity is not being destroyed.
                    entityManager -> getEntity(components[componentIndex]) -> deregisterComponent(getSystemID());
                }
                if (componentIndex != size() - 1 && size() > 1) {
                    // Swap the component to remove with the last component and update the entity of the swapped component.
                    components[componentIndex] = components.back();
                    entityManager -> getEntity(components[componentIndex]) -> updateCommponent(getSystemID(), componentIndex);
                    components.pop_back();
                    return components[componentIndex].getOwningEntityID();
                } else {
                    int eID = components[componentIndex].getOwningEntityID();
                    components.pop_back();
                    return eID;
                }
            }
        }

        // Get a reference to a component.
        ComponentType* getComponentByIndex(int index) {
            return &components[index];
        }

        // Get a reference to a component by its owning entity id.
        ComponentType* getComponentByEntityID(int eID) {
            int index = entityManager -> getEntity(eID) -> getComponentIndexByID(getSystemID());
            if (index != -1) {
                return getComponentByIndex(index);
            } else {
                return NULL;
            }
        }

        ComponentType* getComponentByMatchingComponent(Component& component) {
            int index = entityManager -> getEntity(component) -> getComponentIndexByID(getSystemID());
            if (index != -1) {
                return getComponentByIndex(index);
            } else {
                return NULL;
            }
        }

        ComponentType* getComponentByMatchingComponent(Component* component) {
            int index = entityManager -> getEntity(component) -> getComponentIndexByID(getSystemID());
            if (index != -1) {
                return getComponentByIndex(index);
            } else {
                return NULL;
            }
        }

        int size() {
            return components.size();
        }

        virtual void update(float frametime) = 0;
    protected:
        std::vector<ComponentType> components;
        EntityManager* entityManager;
};

#endif
