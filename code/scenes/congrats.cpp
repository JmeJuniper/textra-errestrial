/******************************************************************************
 * congrats.cpp
 * Source file for congrats.hpp
 * Represents the end scene
 * Impliments the handleInput, start, render, and end functions of the end scene
******************************************************************************/

#include "scenes/credits.hpp"
#include "menu/MenuItem.hpp"
#include "globals.hpp"
#include "fonts.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

// Keep file variables isolated to this file
namespace {
    Texture menuImage("assets\\images\\menu_background.png");
    Sprite background(menuImage);
}

Scene congrats(
    // Input Handler
    [](globals& data, RenderWindow& window, const Event& event)
    {
    },
    
    // Scene enter
    [](globals& data, RenderWindow& window)
    {
        // Sets the menuImage sprite to the same size as the screen
        background.setScale({
            data.windowSize.x / static_cast<float>(menuImage.getSize().x),
            data.windowSize.y / static_cast<float>(menuImage.getSize().y)
        });

        // And make it a bit transparent
        background.setColor(Color(255, 255, 255, 100));
    },
    
    // Renderer
    [](globals& data, RenderWindow& window)
    {
        auto mouse = static_cast<Vector2f>(Mouse::getPosition(window));
        
        // Draw text
        window.draw(background); 
    },
    
    // Scene exit
    [](globals& data, RenderWindow& window)
    {
    
    }
);