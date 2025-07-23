/******************************************************************************
 * menu.cpp
 * Source file for menu.hpp
 * Represents the main menu presented at the start of the game
 * Impliments the handleInput, start, render, and end functions of the menu scene
******************************************************************************/

#include "globals.hpp"
#include "fonts.hpp"
#include "scenes/menu.hpp"
#include "menu/MenuItem.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <exception>
#include <vector>
#include <optional>

using namespace sf;

// Keep file variables isolated to this file
namespace {
    Texture menuImage("assets\\images\\menu_background.png");
    Sprite background(menuImage);
    Text title(TEKTUR, "Textra Errestrial");
    std::vector<MenuItem> menuBtns;
}

Scene menu(
    // Input Handler
    [](globals& data, RenderWindow& window, const Event& event)
    {
        // Handle mouse press
        if (const auto* btnEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
            
            // Loop through each menu button
            for (MenuItem btn: menuBtns) {
                
                // If it's clicked, run the callback function attached
                if (
                    btn.box.getGlobalBounds().contains(
                        static_cast<Vector2f>(
                            btnEvent -> position
                        )
                    )
                )
                    btn.callback(data, window);
            }
        }
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

        // Create title
        title.setCharacterSize(40);
        title.setFillColor(sf::Color::White);
        title.setOutlineColor(sf::Color::Black);
        title.setOutlineThickness(2);
        title.setStyle(sf::Text::Bold);
        title.setPosition({130, 100});
        
        // Create menu buttons
        menuBtns = {
            MenuItem(
                "Play",
                100, 250,
                TEKTUR,
                [](globals &data, RenderWindow &window)
                {
                    data.curScene = "game";
                }
            ),
            MenuItem(
                "Credits",
                100, 400,
                TEKTUR,
                [](globals &data, RenderWindow &window)
                {
                    data.curScene = "credits";
                }
            ),

            MenuItem(
                "Controls",
                380, 250,
                TEKTUR,
                [](globals &data, RenderWindow &window)
                {
                    data.curScene = "pause"; //pause menu has controls
                }
            ),


            MenuItem(
                "Exit",
                380, 400,
                TEKTUR,
                [](globals &data, RenderWindow &window)
                {
                    window.close();
                }
            )
        };
    },
    
    // Renderer
    [](globals& data, RenderWindow& window)
    {
        auto mouse = static_cast<Vector2f>(Mouse::getPosition(window));
        
        window.draw(background);
        window.draw(title);
        
        // Draw buttons
        for (MenuItem btn: menuBtns) {
            // Mouseover effect
            if (btn.box.getGlobalBounds().contains(mouse))
                btn.box.setFillColor(Color(100, 100, 100));
            else
                btn.box.setFillColor(Color(70, 70, 70));
            window.draw(btn.box);
            window.draw(btn.label);
        }
    },
    
    // Scene exit
    [](globals& data, RenderWindow& window)
    {
    
    }
);