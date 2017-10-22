#include "ResourceManager.hpp"

namespace StealthEngine {
    bool ResourceManager::remove(const std::string& filename) {
        return resources.erase(filename);
    }
} /* StealthEngine */
