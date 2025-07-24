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
    sf::Vector2i curMapPos(1, 0);
}

void switchMap(globals &data) {
    // Get the position of the player
    auto playerPos = player -> pos;

    // Create a new map, and load the appropriate tilemap
    map = Map();
    map.loadTilemap(data.gridSize.x, data.gridSize.y, "data/levels/" + std::to_string(curMapPos.x) + std::to_string(curMapPos.y) + "/tilemap.txt");

    // Wrap player position if off-map
    while (playerPos.y < 0)
        playerPos.y += data.gridSize.y;
    while (playerPos.y >= data.gridSize.y)
        playerPos.y -= data.gridSize.y;
    while (playerPos.x < 0)
        playerPos.x += data.gridSize.x;
    while (playerPos.x >= data.gridSize.x)
        playerPos.x -= data.gridSize.x;
    
    // Create new player at proper position
    player = std::static_pointer_cast<Player>(map.placePlayer(playerPos.x, playerPos.y));
}

Scene game(
    // Input Handler
    [](globals &data, RenderWindow &window, Event event)
    {
        // Get keyboard input
        if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>()) {
            // Move player on arrow keys, and change map if moved offscreen
            if (keyEvent -> code == sf::Keyboard::Key::Up)
            {
                player -> tryMove({ 0, -1});
                if (player -> offMap)
                    curMapPos.y -= 1;
            }
            if (keyEvent -> code == sf::Keyboard::Key::Down)
            {
                player -> tryMove({ 0,  1});
                if (player -> offMap)
                    curMapPos.y += 1;
            }
            if (keyEvent -> code == sf::Keyboard::Key::Left)
            {
                player -> tryMove({-1,  0});
                if (player -> offMap)
                    curMapPos.x -= 1;
            }
            if (keyEvent -> code == sf::Keyboard::Key::Right)
            {
                player -> tryMove({ 1,  0});
                if (player -> offMap)
                    curMapPos.x += 1;
            }

            // If the player is moved offscreen, the map needs to be switched
            if (player -> offMap)
                switchMap(data);
        }
    },
    
    // Scene enter
    [](globals &data, RenderWindow &window)
    {
        map.loadTilemap(data.gridSize.x, data.gridSize.y, "data/levels/10/tilemap.txt");
        
        // Add the player to the tilemap
        player = std::static_pointer_cast<Player>(map.placePlayer(3, 3));
    },
    
    // Renderer
    [](globals &data, RenderWindow &window)
    {
        map.draw(window, data.tileSize);
    },
    
    // Scene exit
    [](globals &data, RenderWindow &window)
    {
    
    }
);