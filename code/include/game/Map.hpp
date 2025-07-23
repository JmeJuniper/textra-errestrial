/******************************************************************************
 * Map.hpp
 * Header file for Map.cpp
 * Contains a tilemap of Interactables
 * 
******************************************************************************/

#ifndef MAP_H
    #define MAP_H
    
    #include <vector>
    #include <SFML/Graphics.hpp>
    #include "game/objects/Object.hpp"
    #include <memory>
    
    class Map {
        public:
        // Constructor
        Map() {};
        
        // Loads a tilemap from a file and adds it to the map
        // filePath          [string] - Path to the file to load the tilemap from
        void loadTilemap(size_t width, size_t height, std::string filePath);
        
        // Returns a vector containing all objects on a tile
        // x           [unsigned int] - x position of the tile to retrieve;
        // y           [unsigned int] - x position of the tile to retrieve;
        // ->        [vector<Object>] - A list of all Objects on the retrieved tile
        std::vector<std::unique_ptr<Object>>& getTile(size_t x, size_t y);
        
        // Renders the map at a specified tile size
        // window [sf::RenderWindow&] - Reference to the window to draw the map on
        // tileSize    [unsigned int] - Size, in pixels, of each tile (1:1 aspect ratio assumed)
        void draw(sf::RenderWindow& window, unsigned int tileSize);
        
        private:
        std::vector<
            std::vector<
                std::vector<
                    std::unique_ptr<Object>
                >
            >
        > tlmp;
    };
#endif