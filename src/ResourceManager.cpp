#include "GameEngine2D/ResourceManager.hpp"
#include <fstream>

ResourceManager::ResourceManager() {
}

void ResourceManager::addResourceDirectory(const std::string& resourceDirectory) {
    // If the directory is not already contained in the list then add it.
    if (std::find(resourceDirectories.begin(), resourceDirectories.end(), resourceDirectory) == resourceDirectories.end()) {
        resourceDirectories.push_back(resourceDirectory);
    }
}

void ResourceManager::removeResourceDirectory(const std::string& resourceDirectory) {
    // Remove the directory if it is in the list.
    std::vector<std::string>::iterator dir = std::find(resourceDirectories.begin(), resourceDirectories.end(), resourceDirectory);
    if (dir != resourceDirectories.end()) {
        resourceDirectories.erase(dir);
    }
}

const sf::Texture& ResourceManager::getTexture(const std::string& filename) {
    return getResource(filename, this -> textures);
}

void ResourceManager::deleteTexture(const std::string& filename) {
    textures.erase(getFilePath(filename));
}

void ResourceManager::deleteTexture(const sf::Texture& texture) {
    deleteResource(texture, this -> textures);
}

std::string ResourceManager::getFilePath(const std::string& filename) {
    // Check if the path provided exists.
    if (std::ifstream(filename.c_str())) {
        return filename;
    }
    // Otherwise check the provided resource directories.
    for (std::vector<std::string>::iterator dir = resourceDirectories.begin(); dir != resourceDirectories.end(); dir++) {
        if (std::ifstream((*dir + filename).c_str())) {
            return *dir + filename;
        }
    }
    // If the file cannot be found just return the provided path.
    return filename;
}
