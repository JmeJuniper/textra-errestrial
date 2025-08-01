/******************************************************************************
 * Map.hpp
 * Header file for Map.cpp
 * Contains a tilemap of Objects
 * 
 * Defines Map class:
 * * Constructor
 * * loadTilemap
 * * * Parameters
 * * * * width [size_t]
 * * * * * Width of the tilemap, in tiles.
 * * * * height [size_t]
 * * * * * Height of the tilemap, in tiles.
 * * * * filePath [std::string]
 * * * * * Path to the file to load the tilemap from.
 * * * Return [void]
 * * place
 * * * Template Parameters
 * * * * T [typename]
 * * * * * Type of object to place. Must be an Object or a subclass of an Object.
 * * * Parameters
 * * * * x [size_t]
 * * * * * x position of the object to place.
 * * * * y [size_t]
 * * * * * y position of the object to place.
 * * * * spriteName [std::string]
 * * * * * File name (including extension) of the sprite to intialize the object with.
 * * * Return [std::shared_ptr<T>]
 * * * * Shared pointer to the just-placed object.
 * * getTile
 * * * Parameters
 * * * * x [size_t]
 * * * * * x position of the tile to retrieve.
 * * * * y [size_t]
 * * * * * y position of the tile to retrieve.
 * * * Return [std::vector<std::shared_ptr<Object>>&]
 * * * * A mutable reference to the tile requested—A vector of shared pointers
 * * * * to Objects.
 * * draw
 * * * Parameters
 * * * * window [sf::RenderWindow&]
 * * * * * Reference to the window to draw the map on
 * * * * tileSize [unsigned int]
 * * * * * Size, in pixels, of each tile (1:1 aspect ratio assumed).
 * * * Return [void]
******************************************************************************/

#ifndef MAP_H
    #define MAP_H
    
    #include <vector>
    #include <memory>
    #include <SFML/Graphics.hpp>
    #include "game/objects/Object.hpp"
    #include "game/objects/Player.hpp"
    #include "game/objects/Box.hpp"
    #include "game/objects/Console.hpp"
    #include "game/objects/Comms.hpp"
    
    class Map {
        public:
        // Constructor
        Map() {};
        
        // Loads a tilemap from a file and adds it to the map
        // width                             [size_t] - Width of the tilemap, in tiles
        // height                            [size_t] - Height of the tilemap, in tiles
        // filePath                     [std::string] - Path to the file to load the tilemap from
        void loadTilemap(size_t width, size_t height, std::string filePath);
        
        // Places an object on the map
        // T                               [typename] - Type of object to place. Must be an Object or a subclass of an Object
        // x                                 [size_t] - x position of the object to place
        // y                                 [size_t] - y position of the object to place
        // spriteName                   [std::string] - File name (including extension) of the sprite to intialize the object with
        // ->                    [std::shared_ptr<T>] - Shared pointer to the just-placed object
        template <typename T>
        std::shared_ptr<T> place(size_t x, size_t y, std::string spriteName)
        {
            // Create a player object and a pointer to it
            std::shared_ptr<Object> playerPtr = std::make_shared<T>(
                spriteName,
                sf::Vector2i{static_cast<int>(x), static_cast<int>(y)},
                this
            );
            
            // Insert it to the proper positions, and return it
            tlmp[x][y].push_back(playerPtr);
            return std::move(std::static_pointer_cast<T>(playerPtr));
        }
        
        // Returns a vector containing all objects on a tile
        // x                                 [size_t] - x position of the tile to retrieve
        // y                                 [size_t] - y position of the tile to retrieve
        // -> [std::vector<std::shared_ptr<Object>>&] - A mutable reference to the tile requested—A vector of shared pointers to Objects
        std::vector<std::shared_ptr<Object>>& getTile(size_t x, size_t y);
        
        // Renders the map at a specified tile size
        // window                 [sf::RenderWindow&] - Reference to the window to draw the map on
        // tileSize                    [unsigned int] - Size, in pixels, of each tile (1:1 aspect ratio assumed)
        void draw(sf::RenderWindow& window, unsigned int tileSize);
        
        private:
        std::vector<
            std::vector<
                std::vector<
                    std::shared_ptr<Object>
                >
            >
        > tlmp;
    };
#endif