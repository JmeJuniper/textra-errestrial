/******************************************************************************
 * console.cpp
 * Source file for console.hpp
 * Represents the console scene, when the player interacts with a console.
 * Impliments the handleInput, start, render, and end functions of the console scene
******************************************************************************/

#include "scenes/console.hpp"
#include "menu/MenuItem.hpp"
#include "globals.hpp"
#include "fonts.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>


using namespace sf;

// Keep file variables isolated to this file
namespace {
    // Resume Game
    MenuItem resumeBtn(
        "Exit Console",
        220, 500,
        TEKTUR,
        [](globals& data, RenderWindow& window){ data.curScene = "game"; }  
    );

    Texture screenTx({640, 450});
    Sprite screen(screenTx);
}

Scene console(
    // Input Handler
    [](globals& data, RenderWindow& window, const Event& event)
    {
        if (const auto* btnEvent = event.getIf<Event::MouseButtonPressed>()) {

            if (
                resumeBtn.box.getGlobalBounds().contains(
                    static_cast<Vector2f>(btnEvent -> position)
                )
            )
                resumeBtn.callback(data, window);
        }
    },

    // Scene enter
    [](globals& data, RenderWindow& window)
    {
        // Load current console image
        if (not screenTx.loadFromFile(data.consoleImg))
        {
            std::cerr << "Could not load " << data.consoleImg << std::endl;
        }

        // and assign it to the proper sprite
        screen.setTexture(screenTx);
    },

    // Renderer
    [](globals& data, RenderWindow& window)
    {
        auto mouse = static_cast<Vector2f>(Mouse::getPosition(window));
        
        window.draw(screen);

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