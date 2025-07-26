/******************************************************************************
 * pause.cpp
 * Source file for pause.hpp
 * Represents the pause/introduction scene
 * Impliments the handleInput, start, render, and end functions of the pause scene
******************************************************************************/

#include "scenes/pause.hpp"
#include "menu/MenuItem.hpp"
#include "globals.hpp"
#include "fonts.hpp"
#include <SFML/Graphics.hpp>


using namespace sf;

// Keep file variables isolated to this file
namespace {
    Texture menuImage("assets\\images\\menu_background.png");  
    Sprite background(menuImage);

    Text pausedTitle(TEKTUR, "PAUSED");
    Text introLine(TEKTUR,
        "You've found yourself on an alien ship, with no recollection of why.\n"
        "Figure out the language using clues to determine what the glyphs mean.\n"
        "Learn how to call for help.\n"
        "Escape."
    ); 
    Text controlsTitle(TEKTUR, "CONTROLS:");
    Text controls(TEKTUR,
        "Arrow Keys - Move Around\n"
        "Escape - Pause          \n"
    );
    
    // Resume previous scene
    MenuItem resumeBtn(
        "Back",
        220, 500,
        TEKTUR,
        [](globals& data, RenderWindow& window){ data.curScene = data.returnFromPause; }  
    );
}

Scene pause(
    // Input Handler
    [](globals& data, RenderWindow& window, const Event& event)
    {
        if (const auto* btnEvent = event.getIf<sf::Event::MouseButtonPressed>()) {

            if (
                resumeBtn.box.getGlobalBounds().contains(
                    static_cast<Vector2f>(btnEvent->position)
                )
            )
                resumeBtn.callback(data, window);
        }
    },
    
    // Scene enter
    [](globals& data, RenderWindow& window)
    {
        // Scale background image to window size
        background.setScale({
            data.windowSize.x / static_cast<float>(menuImage.getSize().x),
            data.windowSize.y / static_cast<float>(menuImage.getSize().y)
        });

        // Transparent
        background.setColor(Color(255, 255, 255, 100));  
        
        // Title setup
        pausedTitle.setCharacterSize(40);
        pausedTitle.setFillColor(Color::White);
        pausedTitle.setOutlineColor(Color::Black);
        pausedTitle.setOutlineThickness(2);
        pausedTitle.setStyle(Text::Bold);
        pausedTitle.setPosition({data.windowSize.x/2 - pausedTitle.getGlobalBounds().size.x/2, 100});
        
        // Intro setup
        introLine.setCharacterSize(15);
        introLine.setFillColor(Color::White);
        introLine.setPosition({data.windowSize.x/2 - introLine.getGlobalBounds().size.x/2, 150});
        
        // Controls Title
        controlsTitle.setCharacterSize(28);
        controlsTitle.setFillColor(Color::White);
        controlsTitle.setOutlineColor(Color::Black);
        controlsTitle.setOutlineThickness(2);
        controlsTitle.setStyle(Text::Bold);
        controlsTitle.setPosition({data.windowSize.x/2 - controlsTitle.getGlobalBounds().size.x/2, 260});
        
        // Control details
        controls.setCharacterSize(22);
        controls.setFillColor(Color::White);
        controls.setPosition({data.windowSize.x/2 - controls.getGlobalBounds().size.x/2, 310});
    },

    // Renderer
    [](globals& data, RenderWindow& window)
    {
        auto mouse = static_cast<Vector2f>(Mouse::getPosition(window));

        window.draw(background);
        window.draw(pausedTitle);
        window.draw(introLine);
        window.draw(controlsTitle);
        window.draw(controls);

        // Mouse hover for Resume button
        if (resumeBtn.box.getGlobalBounds().contains(mouse))
            resumeBtn.box.setFillColor(Color(100, 100, 100));
        else
            resumeBtn.box.setFillColor(Color(70, 70, 70));

        window.draw(resumeBtn.box);
        window.draw(resumeBtn.label);
    },
    
    // Scene exit
    [](globals& data, RenderWindow& window)
    {
        // No cleanup needed
    }
);