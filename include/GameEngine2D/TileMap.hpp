#ifndef TILE_MAP_H
#define TILE_MAP_H
#include <SFML/Graphics.hpp>
#include <unordered_map>

template <class T>
class Tile {
    public:
        Tile() {};
    private:
        std::unordered_map<int, T> contents;
};

template <class T>
class TileMap {
    public:
        TileMap(const sf::Vector2i& dimensions) {
            width = dimensions.x;
            height = dimensions.y;
        }
        Tile& at(int x, int y) {
            if (x > 0 && y > 0 && x < width && y < height) {
                return tiles[x + y * width];
            } else {
                throw std::out_of_bounds("Tile does not exist.");
            }
        }
    private:
        int width, height;
        // Each tile is an unordered_map and the TileMap is an unordered_map of tiles.
        std::unordered_map<int, Tile> tiles;
};

#endif
