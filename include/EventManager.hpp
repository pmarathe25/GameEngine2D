#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H
#include <unordered_map>
#include <vector>
#include <functional>
#include <any>


#include <typeinfo>
#include <iostream>
#include <SFML/System.hpp>


namespace StealthEngine {
    class EventManager {
        public:
            enum EventID {
                POSITION_CHANGED = 0,
            };

            EventManager() { }

            template <EventID id, typename... Args>
            void post(Args&&... args) {
                for (auto& callback : callbacks[id]) {
                    std::any_cast<std::function<void(Args...)>>(callback)(args...);
                    // reinterpret_cast<std::function<void(Args...)>>(callback)(args...);
                    // reinterpret_cast<std::function<void(int, const sf::Vector2f&)>>(callback)(std::forward<Args>(args)...);
                    // std::any_cast<std::function<void(int, const sf::Vector2f&)>>(callback)(std::forward<Args>(args)...);
                }
            }

            template <EventID id, typename... Args>
            void request(std::function<void(Args...)> callback) {
                callbacks[id].push_back(callback);
            }

        private:
            // std::unordered_map<EventID, std::vector<std::function<void(void)>>> callbacks;
            std::unordered_map<EventID, std::vector<std::any>> callbacks;
    };
} /* StealthEngine */

#endif
