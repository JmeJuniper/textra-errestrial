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
    Text introLine(TEKTUR, "FIXME WHEN WE GET AN INTRO WRITTEN");  // Editable intro FIXMEEEEE
    Text controlsTitle(TEKTUR, "CONTROLS:");
    Text controlMove(TEKTUR, "Arrow Keys - Move Around");
    Text controlInteract(TEKTUR, "Spacebar - Interact with Objects");

    // Resume Game
    MenuItem resumeBtn(
        "Resume Game",
        150, 500,  // Left button X pos
        TEKTUR,
        [](globals& data, RenderWindow& window){ data.curScene = "game"; }  
    );

    // Exit to menu
    MenuItem quitBtn(
        "Quit to Menu",
        350, 500,  // Right button X pos
        TEKTUR,
        [](globals& data, RenderWindow& window){ data.curScene = "menu"; }  
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
            else if (
                quitBtn.box.getGlobalBounds().contains(
                    static_cast<Vector2f>(btnEvent->position)
                )
            )
                quitBtn.callback(data, window);
        },
    }

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
        pausedTitle.setPosition({220, 100});

        // Intro line setup
        introLine.setCharacterSize(24);
        introLine.setFillColor(Color::White);
        introLine.setOutlineColor(Color::Black);
        introLine.setOutlineThickness(1);
        introLine.setPosition({90, 170});

        // Controls Title
        controlsTitle.setCharacterSize(28);
        controlsTitle.setFillColor(Color::White);
        controlsTitle.setOutlineColor(Color::Black);
        controlsTitle.setOutlineThickness(2);
        controlsTitle.setStyle(Text::Bold);
        controlsTitle.setPosition({240, 250});

        // Control details
        controlMove.setCharacterSize(22);
        controlMove.setFillColor(Color::White);
        controlMove.setPosition({200, 300});

        controlInteract.setCharacterSize(22);
        controlInteract.setFillColor(Color::White);
        controlInteract.setPosition({200, 330});
    },

    // Renderer
    [](globals& data, RenderWindow& window)
    {
        auto mouse = static_cast<Vector2f>(Mouse::getPosition(window));

        window.draw(background);
        window.draw(pausedTitle);
        window.draw(introLine);
        window.draw(controlsTitle);
        window.draw(controlMove);
        window.draw(controlInteract);

        // Mouse hover for Resume button
        if (resumeBtn.box.getGlobalBounds().contains(mouse))
            resumeBtn.box.setFillColor(Color(100, 100, 100));
        else
            resumeBtn.box.setFillColor(Color(70, 70, 70));

        // Mouse hover for Quit button
        if (quitBtn.box.getGlobalBounds().contains(mouse))
            quitBtn.box.setFillColor(Color(100, 100, 100));
        else
            quitBtn.box.setFillColor(Color(70, 70, 70));

        window.draw(resumeBtn.box);
        window.draw(resumeBtn.label);

        window.draw(quitBtn.box);
        window.draw(quitBtn.label);
    },

    // Scene exit
    [](globals& data, RenderWindow& window)
    {
        // No cleanup needed
    }
);