/******************************************************************************
 * Map.cpp
 * Source file for Map.hpp
 * Contains a tilemap of Interactables
******************************************************************************/

#include "game/Map.hpp"

#include <fstream>
#include <exception>
#include <iostream>
#include "game/tilemapFuncs.hpp"
#include "game/objects/Floor.hpp"
#include "game/objects/Wall.hpp"
#include "game/objects/Player.hpp"

void Map::loadTilemap(size_t width, size_t height, std::string filePath)
{
    std::ifstream tlmpReader(filePath);
    
    // Throw error if filePath can't be opened
    if (not tlmpReader.is_open())
        throw std::ios_base::failure("Cannot open " + filePath);
    
    // Size vector grid properly
    tlmp.resize(width);
    for (auto& col: tlmp)
    {
        col.resize(height);
    }
    
    // Read tiles from tilemap
    std::string row;
    int x, y = 0;
    while (std::getline(tlmpReader, row))
    {
        x = 0;
        tlmp.emplace_back();
        for (char tile: row)
        {
            // Get the image represented by the current tile
            auto tileData = cttl[tile];
            
            // TODO: support things that aren't floors. lmao
            // There's probably some better way to do this but :p
            switch (tileData.second)
            {
                case 'F':
                    tlmp[x][y].emplace_back(std::make_shared<Floor>(
                        tileData.first,
                        sf::Vector2i{x, y},
                        this
                    ));
                    break;
                
                case 'W':
                    tlmp[x][y].emplace_back(std::make_shared<Wall>(
                        tileData.first,
                        sf::Vector2i{x, y},
                        this
                    ));
                    break;
            }
            
            x++;
        }
        y++;
    }

    tlmpReader.close();
}


// Disable "no return type" warning.
// The code will already throw an error if no return can be given and there
// is no reasonable default return that can be given in that event.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"

std::vector<std::shared_ptr<Object>>&
Map::getTile(size_t x, size_t y)
{
    return tlmp.at(x).at(y);
}

// Undisable warning
#pragma GCC diagnostic pop



void Map::draw(sf::RenderWindow& window, unsigned int tileSize)
{
    // Store position in loop
    size_t x, y;

    // Loop through each column in the tilemap (left -> right)
    for (auto& col: tlmp)
    {
        // Loop through each tile in the column (top -> bottom)
        for (auto& tile: col)
        {
            // Loop through each object on the tile (bottom -> top)
            for (auto& obj: tile)
                // Render the object
                obj -> draw(window, x, y, tileSize);
            y++;
        }
        x++;
    }
}