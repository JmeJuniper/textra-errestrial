/******************************************************************************
 * game.cpp
 * Source file for game.hpp
 * Represents the main game scene
 * Impliments the handleInput, start, render, and end functions of the game scene
******************************************************************************/

#include "scenes/game.hpp"
#include "game/Map.hpp"
#include "globals.hpp"
#include "fonts.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace {
    Map map;
}

Scene game(
    // Input Handler
    [](globals &data, RenderWindow &window, Event event)
    {
        
    },
    
    // Scene enter
    [](globals &data, RenderWindow &window)
    {
        map.loadTilemap(10, 10, "data/levels/10.txt");
    },
    
    // Renderer
    [](globals &data, RenderWindow &window)
    {
        map.draw(window, 64);
    },
    
    // Scene exit
    [](globals &data, RenderWindow &window)
    {
    
    }
);