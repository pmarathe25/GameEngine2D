#include "Entity/EntityGroup.hpp"

namespace StealthEngine {
    void EntityGroup::push_back(const Entity& entity) {
        if (std::find(begin(), end(), entity) == end()) {
            std::vector<Entity>::push_back(entity);
        }
    }

    void EntityGroup::push_back(Entity&& entity) {
        if (std::find(begin(), end(), entity) == end()) {
            std::vector<Entity>::push_back(std::move(entity));
        }
    }

    bool EntityGroup::removeFromGroup(Entity entity) {
        for (int i = 0; i < size(); ++i) {
            if ((*this)[i] == entity) {
                (*this)[i] = back();
                pop_back();
                return true;
            }
        }
        return false;
    }

    void EntityGroup::push_back_unsafe(Entity entity) {
        std::vector<Entity>::push_back(entity);
    }
} /* StealthEngine */
