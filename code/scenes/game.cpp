/******************************************************************************
 * game.cpp
 * Source file for game.hpp
 * Represents the main game scene
 * Impliments the handleInput, start, render, and end functions of the game scene
******************************************************************************/

#include "scenes/game.hpp"
#include "globals.hpp"
#include "fonts.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

Scene game(
    // Input Handler
    [](globals &data, RenderWindow &window, Event event)
    {
        
    },
    
    // Scene enter
    [](globals &data, RenderWindow &window)
    {

    },
    
    // Renderer
    [](globals &data, RenderWindow &window)
    {
        // Create text label and get its size
        Text label(TEKTUR, "Game Scene", 30);
        Vector2 labelSize = label.getLocalBounds().size;

        // Center label
        label.setPosition({data.windowSize.x - labelSize.x/2, data.windowSize.y - labelSize.y/2}); 
        
        window.draw(label);
    },
    
    // Scene exit
    [](globals &data, RenderWindow &window)
    {
    
    }
);