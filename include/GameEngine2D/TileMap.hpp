#ifndef TILE_MAP_H
#define TILE_MAP_H
#include <SFML/Graphics.hpp>
#include <unordered_map>

template <class T>
class TileMap {
    public:
        TileMap(const sf::Vector2i& dimensions) {

        }
    private:
        int width, height;
        // Each tile is an unordered_map and the TileMap is an unordered_map of tiles.
        std::unordered_map<std::unordered_map<T> > tiles;
};

#endif
