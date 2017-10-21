#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <variant>
#include <string>

namespace StealthEngine {
    class ResourceManager {
        public:
            ResourceManager() { }
            // Get a resource if it's in the map, otherwise load from file.
            template <typename Resource>
            const Resource& get(const std::string& filename) {
                if (resources.count(filename) < 1) {
                    std::get<Resource>(resources[filename]).loadFromFile(filename);
                }
                return std::get<Resource>(resources[filename]);
            }
            // Delete a resource.
            bool remove(const std::string& filename) {
                return resources.erase(filename);
            }
        private:
            std::unordered_map<std::string, std::variant<sf::Texture>> resources;
    };
} /* StealthEngine */

#endif
