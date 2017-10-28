#ifndef ENTITY_GROUP_H
#define ENTITY_GROUP_H

namespace StealthEngine {
    class EntityGroup : public std::vector<Entity> {
        template <typename SystemManager>
        friend class EntityFactory;

        public:
            void push_back(const Entity& entity) {
                if (std::find(begin(), end(), entity) == end()) {
                    std::vector<Entity>::push_back(entity);
                }
            }

            void push_back(Entity&& entity) {
                if (std::find(begin(), end(), entity) == end()) {
                    std::vector<Entity>::push_back(std::move(entity));
                }
            }

            bool removeFromGroup(Entity entity) {
                for (int i = 0; i < size(); ++i) {
                    if ((*this)[i] == entity) {
                        (*this)[i] = back();
                        pop_back();
                        return true;
                    }
                }
                return false;
            }
        private:
            void push_back_unsafe(Entity entity) {
                std::vector<Entity>::push_back(entity);
            }
    };

} /* StealthEngine */

#endif
