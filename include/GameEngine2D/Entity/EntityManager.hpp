#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

class EntityManager {
    public:
        EntityManager(const RenderSystem& renderSystem);
        int getNewEntity();
        void attachComponent(int eID, const Component& component);
    private:
        std::vector<Entity> entities;
        std::vector<int> freeIDs;
        RenderSystem renderModule;
};

#endif
