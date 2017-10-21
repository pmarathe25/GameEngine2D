#ifndef TILE_MAP_H
#define TILE_MAP_H
#include <SFML/Graphics.hpp>
#include <unordered_map>

template <class T>
class Tile {
    public:
        Tile() {};
        // Addition
        void insert(int key, const T& value) {
            contents[key] = value;
        }
        // Retrieval
        T& at(int key) {
            if (contents.count(key) > 0) {
                return contents[key];
            } else {
                throw std::out_of_bounds("Key does not exist in this tile.");
            }
        }
        T& operator[](int key) {
            return contents[key];
        }
        // Deletion
        void erase(int key) {
            contents.erase(key);
        }
    private:
        std::unordered_map<int, T> contents;
};

template <class T>
class TileMap {
    public:
        TileMap(int numRows, int numCols) {
            width = numCols;
            height = numRows;
            sz = width * height;
            // Initialize the map.
            for (int i = size - 1; i >= 0; --i) {
                tiles[i] = Tile<T>();
            }
        }
        Tile& at(int row, int col) {
            if (x > 0 && y > 0 && row < numRows && col < numCols) {
                return tiles[row * numCols + col];
            } else {
                throw std::out_of_bounds("Tile does not exist.");
            }
        }
        int size() {
            return sz;
        }
    private:
        int width, height, sz;
        // Each tile is an unordered_map and the TileMap is an unordered_map of tiles.
        std::unordered_map<int, Tile<T> > tiles;
};

#endif
