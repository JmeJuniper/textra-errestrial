/******************************************************************************
 * Comms.cpp
 * Source file for Comms.hpp
 * Class for consoles that block movement but display an interactive screen.
******************************************************************************/

#include "game/objects/Comms.hpp"

bool Comms::tryMove(sf::Vector2i diff)
{
    // If the console is interacted with, note it in a boolean
    interacted = true;
    
    // Consoles are solid objects, and cannot be moved into
    return false;
}