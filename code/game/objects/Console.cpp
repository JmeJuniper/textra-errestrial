/******************************************************************************
 * Console.cpp
 * Source file for Console.hpp
 * Class for consoles that block movement but display a screen on interaction.
******************************************************************************/

#include "game/objects/Console.hpp"
#include "game/Map.hpp"
#include <iostream>

bool Console::tryMove(sf::Vector2i diff)
{
    // If the console is interacted with, note it in a boolean
    interacted = true;
    
    // Consoles are solid objects, and cannot be moved into
    return false;
}