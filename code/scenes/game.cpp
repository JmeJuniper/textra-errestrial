/******************************************************************************
 * game.cpp
 * Source file for game.hpp
 * Represents the main game scene
 * Impliments the handleInput, start, render, and end functions of the game scene
******************************************************************************/

#include <memory>
#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include "fonts.hpp"
#include "scenes/game.hpp"
#include "game/Map.hpp"
#include "game/objects/Player.hpp"

using namespace sf;

namespace {
    Map map;
    std::shared_ptr<Player> player;
}

Scene game(
    // Input Handler
    [](globals &data, RenderWindow &window, Event event)
    {
        // Get keyboard input
        if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>()) {
            // Move player on arrow keys
            if (keyEvent -> code == sf::Keyboard::Key::Up)
                player -> tryMove({ 0, -1});
            if (keyEvent -> code == sf::Keyboard::Key::Down)
                player -> tryMove({ 0,  1});
            if (keyEvent -> code == sf::Keyboard::Key::Left)
                player -> tryMove({-1,  0});
            if (keyEvent -> code == sf::Keyboard::Key::Right)
                player -> tryMove({ 1,  0});
        }
    },
    
    // Scene enter
    [](globals &data, RenderWindow &window)
    {
        map.loadTilemap(10, 10, "data/levels/10/tilemap.txt");
        
        // Add the player to the tilemap
        player = std::static_pointer_cast<Player>(map.placePlayer(3, 3));
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