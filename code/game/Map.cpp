/******************************************************************************
 * Map.cpp
 * Source file for Map.hpp
 * Contains a tilemap of Interactables
******************************************************************************/

#include "game/Map.hpp"

#include <fstream>
#include <vector>
#include <exception>
#include <memory>
#include "game/tilemapFuncs.hpp"
#include "game/objects/Floor.hpp"

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
        for (auto& tile: col)
            tile.reserve(5);
    }
    
    // Read tiles from tilemap
    std::string row;
    int x, y = 0;
    while (std::getline(tlmpReader, row))
    {
        x = 0;
        for (char tile: row)
        {
            // Get the image represented by the current tile
            std::string assetName = cttl[tile];
            
            // TODO: support things that aren't floors. lmao
            tlmp[x][y].push_back(
                std::unique_ptr<Object>(new Floor(
                    assetName,
                    sf::Vector2i{x, y},
                    this
                ))
            );
            
            x++;
        }
        y++;
    }
}

std::vector<std::unique_ptr<Object>>&
Map::getTile(size_t x, size_t y)
{
    return tlmp[x][y];
}

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