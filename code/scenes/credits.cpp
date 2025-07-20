/******************************************************************************
 * credits.cpp
 * Source file for credits.hpp
 * Represents the credits scene
 * Impliments the handleInput, start, render, and end functions of the credits scene
******************************************************************************/

#include "scenes/game.hpp"
#include "menu/MenuItem.hpp"
#include "globals.hpp"
#include "fonts.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

// Keep file variables isolated to this file
namespace {
    Texture menuImage("assets\\images\\menu_background.png");
    Sprite background(menuImage);
    Text title(TEKTUR, "Credits");
    Text authorsHeader(TEKTUR, "Authors:");
    Text authorsBody(TEKTUR,
        "- Hannah Frank\n"
        "- Scott Way\n"
    );
    Text thirdPartyHeader(TEKTUR, "Third-Party Credits:");
    Text thirdPartyBody(TEKTUR,
        "- Tektur Font by Google Fonts\n"
        "- SFML Library\n"
        "- FIX ME FOR THIRD PARTY TILES" // FIXME
    );
    MenuItem backBtn(
        "Back to Menu",
        220, 550,
        TEKTUR,
        [](globals& data, RenderWindow& window){ data.curScene = "menu"; }
    );
}

Scene credits(
    // Input Handler
    [](globals& data, RenderWindow& window, const Event& event)
    {
        // Handle mouse press
        if (const auto* btnEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
            
            // If the back button's clicked, run the callback function attached
            if (
                backBtn.box.getGlobalBounds().contains(
                    static_cast<Vector2f>(
                        btnEvent -> position
                    )
                )
            )
                backBtn.callback(data, window);
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
        
        // Set style of text elements
        title.setCharacterSize(36);
        title.setFillColor(sf::Color::White);
        title.setPosition({230, 30});
        
        authorsHeader.setCharacterSize(24);
        authorsHeader.setFillColor(sf::Color::White);
        authorsHeader.setPosition({50, 100});
        
        authorsBody.setCharacterSize(20);
        authorsBody.setFillColor(sf::Color::White);
        authorsBody.setPosition({70, 140});
        
        thirdPartyHeader.setCharacterSize(24);
        thirdPartyHeader.setFillColor(sf::Color::White);
        thirdPartyHeader.setPosition({50, 230});

        thirdPartyBody.setCharacterSize(20);
        thirdPartyBody.setFillColor(sf::Color::White);
        thirdPartyBody.setPosition({70, 270});
    },
    
    // Renderer
    [](globals& data, RenderWindow& window)
    {
        auto mouse = static_cast<Vector2f>(Mouse::getPosition(window));
        
        // Draw text
        window.draw(background); 
        window.draw(title);
        window.draw(authorsHeader);
        window.draw(authorsBody);
        window.draw(thirdPartyHeader);
        window.draw(thirdPartyBody);
        
        // Back button
        // Mouseover effect
        if (backBtn.box.getGlobalBounds().contains(mouse))
            backBtn.box.setFillColor(Color(100, 100, 100));
        else
            backBtn.box.setFillColor(Color(70, 70, 70));
        window.draw(backBtn.box);
        window.draw(backBtn.label);
    },
    
    // Scene exit
    [](globals& data, RenderWindow& window)
    {
    
    }
);