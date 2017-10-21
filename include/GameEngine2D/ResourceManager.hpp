#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>

class ResourceManager {
    public:
        ResourceManager();
        void addResourceDirectory(const std::string& resourceDirectory);
        void removeResourceDirectory(const std::string& resourceDirectory);
        // Textures.
        const sf::Texture& getTexture(const std::string& filename);
        void deleteTexture(const std::string& filename);
        void deleteTexture(const sf::Texture& texture);
    private:
        std::map<std::string, sf::Texture> textures;
        std::vector<std::string> resourceDirectories;
        std::string getFilePath(const std::string& filename);
        // Deletes any kind of resource from the appropriate map.
        template<typename Resource>
        void deleteResource(const Resource& resource, std::map<std::string, Resource>& resources) {
            for (typename std::map<std::string, Resource>::iterator res = resources.begin(); res != resources.end(); res++) {
                // Check if the resources have the same addresses.
                if (&resource == &(res -> second)) {
                    resources.erase(res);
                    return;
                }
            }
        }
        // Gets any kind of resource.
        template<typename Resource>
        const Resource& getResource(std::string filename, std::map<std::string, Resource>& resources) {
            // This is the full file path under which the resource will be stored.
            filename = getFilePath(filename);
            // Check if the file is already loaded.
            typename std::map<std::string, Resource>::iterator res = resources.find(filename);
            if (res != resources.end()) {
                return res -> second;
            }
            // Otherwise load it from the disk.
            resources[filename] = Resource();
            resources[filename].loadFromFile(filename);
            return resources[filename];
        }
};

#endif
