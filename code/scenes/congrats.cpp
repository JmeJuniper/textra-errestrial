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

    Text congratsLine1(TEKTUR, "CONGRATULATIONS ON");
    Text congratsLine2(TEKTUR, "FINISHING OUR GAME\n(the aliens saved you)");

    MenuItem creditsBtn( // i think i did this right? tried copying the credits one
        "View Credits",
        250, 550,  //FIXME POTENTIAL JUST GUESSING FOR NOW
        TEKTUR,
        [](globals& data, RenderWindow& window){ data.curScene = "credits"; }
    );
}

Scene congrats(
    // Input Handler
    [](globals& data, RenderWindow& window, const Event& event)
    {
        if (const auto* btnEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
            
            // If the credits button's clicked, run the callback function attached
            if (
                creditsBtn.box.getGlobalBounds().contains(
                    static_cast<Vector2f>(
                        btnEvent -> position
                    )
                )
            )
                creditsBtn.callback(data, window);
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

        // Set up text
        congratsLine1.setCharacterSize(36);
        congratsLine1.setFillColor(Color::White);
        congratsLine1.setOutlineColor(Color::Black);
        congratsLine1.setOutlineThickness(2);
        congratsLine1.setStyle(Text::Bold);

        congratsLine2.setCharacterSize(36);
        congratsLine2.setFillColor(Color::White);
        congratsLine2.setOutlineColor(Color::Black);
        congratsLine2.setOutlineThickness(2);
        congratsLine2.setStyle(Text::Bold);

        // FIXME   Set text position (may need fixme)
        congratsLine1.setPosition({80, 150});
        congratsLine2.setPosition({100, 200});
    },
    
    // Renderer
    [](globals& data, RenderWindow& window)
    {
        auto mouse = static_cast<Vector2f>(Mouse::getPosition(window));
        
        // Draw text
        window.draw(background);
        window.draw(congratsLine1);
        window.draw(congratsLine2); 

        // Mouseover effect
        // go to credits
        if (creditsBtn.box.getGlobalBounds().contains(mouse))
            creditsBtn.box.setFillColor(Color(100, 100, 100));
        else
            creditsBtn.box.setFillColor(Color(70, 70, 70));

        window.draw(creditsBtn.box);
        window.draw(creditsBtn.label);
    },
    
    // Scene exit
    [](globals& data, RenderWindow& window)
    {
    
    }
);