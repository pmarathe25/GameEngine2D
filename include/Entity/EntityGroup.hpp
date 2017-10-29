#ifndef ENTITY_GROUP_H
#define ENTITY_GROUP_H
#include "World.hpp"
#include <vector>

namespace StealthEngine {
    class EntityGroup : public std::vector<Entity> {
        // Allow the factory to access push_back_unsafe
        template <typename SystemManager>
        friend class EntityFactory;
        public:
            void push_back(const Entity& entity);
            void push_back(Entity&& entity);
            bool removeFromGroup(Entity entity);
        private:
            void push_back_unsafe(Entity entity);
    };

} /* StealthEngine */

#endif
