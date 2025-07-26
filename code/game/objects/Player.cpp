/******************************************************************************
 * Player.cpp
 * Source file for Player.hpp
 * Class for a player that can move.
******************************************************************************/

#include "game/objects/Player.hpp"
#include "game/Map.hpp"

bool Player::tryMove(sf::Vector2i diff)
{
    // Set sprite based off of movement direction
    auto sprPath = [](std::string dir){ return "assets/sprites/player" + dir + ".png"; };
    bool success;
    if (diff.y < 0)
        success = tex.loadFromFile(sprPath("up"));
    else if (diff.y > 0)
        success = tex.loadFromFile(sprPath("down"));
    else
    {
        if (diff.x < 0)
            success = tex.loadFromFile(sprPath("left"));
        else
            success = tex.loadFromFile(sprPath("right"));
    }
    
    if (success)
        spr.setTexture(tex);
    else
        throw std::ios_base::failure("Could not load player sprite.");
    
    // Calculate new position to move to
    auto newPos = pos + diff;
    
    // Get the tiles at the position being moved to
    std::vector<std::shared_ptr<Object>>* newPosTile = nullptr;
    try
    {
        newPosTile = &(map -> getTile(newPos.x, newPos.y));
    }
    catch (const std::out_of_range& e)
    {
        // IF the player is being moved off-screen:
        // Don't actually move the player in the tilemap, but change their position in-class
        pos = newPos;
        offMap = true;
        return true;
    }
    
    // Also try to grab the tile the player is currently on
    std::vector<std::shared_ptr<Object>>* curTile = nullptr;
    try
    {
        curTile = &(map -> getTile(pos.x, pos.y));
    }
    catch (const std::out_of_range& e)
    {
        // IF the player is already off-screen:
        // Throw an error. The player should not be moving from off-screen to on-screen.
        throw std::runtime_error("Player attempted move from off-screen.");
        return false;
    }
    
    // Find the index of the player in the tile
    size_t playerIdx = curTile -> size();
    for (size_t i = 0; i < curTile -> size(); i++)
        // Check if the element at playerIdx is a pointer to a player object
        if (std::dynamic_pointer_cast<Player>((*curTile)[i]))
        {
            // If so, we've found our player
            playerIdx = i;
            break;
        }
    
    // If we can't find the player, throw an error
    if (playerIdx == curTile -> size())
    {
        throw std::runtime_error("Cannot find player at " + std::to_string(pos.x) + ", " + std::to_string(pos.y));
        return false;
    }
    
    // Try to move all objects on the tile being moved to
    bool movable = true;
    for (auto obj: *newPosTile)
        // If any of them return "false", the tile cannot be moved to
        if (not (obj -> tryMove(diff)))
            movable = false;
    
    // If the tile can be moved to, do so
    if (movable)
    {
        newPosTile -> push_back(std::move((*curTile)[playerIdx]));
        curTile -> erase(curTile -> begin() + playerIdx);
        pos = newPos;
        return true;
    }
    else
        return false;
}