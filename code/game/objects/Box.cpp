/******************************************************************************
 * Box.cpp
 * Source file for Box.hpp
 * Class for a box that can be pushed.
******************************************************************************/

#include "game/objects/Box.hpp"
#include "game/Map.hpp"

bool Box::tryMove(sf::Vector2i diff)
{
    // Calculate new position to move to
    auto newPos = pos + diff;
    
    // Get the tile the box is currently on
    std::vector<std::shared_ptr<Object>>* curTile = nullptr;
    try
    {
        curTile = &(map -> getTile(pos.x, pos.y));
    }
    catch (const std::out_of_range& e)
    {
        // IF the box is already off-screen:
        // Throw an error. The box shouldn't be off-screen??
        throw std::runtime_error("Box attempted move from off-screen.");
        return false;
    }
    
    // Find the index of the box in the tile
    size_t boxIdx = curTile -> size();
    for (size_t i = 0; i < curTile -> size(); i++)
        // Check if the element at boxIdx is a pointer to a box object
        if (std::dynamic_pointer_cast<Box>((*curTile)[i]))
        {
            // If so, we've found our box
            boxIdx = i;
            break;
        }
    
    // If we can't find the box, throw an error
    if (boxIdx == curTile -> size())
    {
        throw std::runtime_error("Cannot find box at " + std::to_string(pos.x) + ", " + std::to_string(pos.y));
        return false;
    }
    
    // Get the tile at the position being moved to
    std::vector<std::shared_ptr<Object>>* newPosTile = nullptr;
    try
    {
        newPosTile = &(map -> getTile(newPos.x, newPos.y));
    }
    catch (const std::out_of_range& e)
    {
        // IF the box is being moved off-screen:
        // uh just delete it ig
        curTile -> erase(curTile -> begin() + boxIdx);
        return true;
    }
    
    // Try to move all objects on the tile being moved to
    bool movable = true;
    for (auto obj: *newPosTile)
        // If any of them return "false", the tile cannot be moved to
        if (not (obj -> tryMove(diff)))
        {
            movable = false;
            break;
        }
    
    // If the tile can be moved to, do so
    if (movable)
    {
        newPosTile -> push_back(std::move((*curTile)[boxIdx]));
        curTile -> erase(curTile -> begin() + boxIdx);
        pos = newPos;
        return true;
    }
    else
    {
        return false;
    }
}