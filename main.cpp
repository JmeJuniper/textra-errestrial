/******************************************************************************
 * main.cpp
 * Main source file
 * Sets up SFML window, handles basic scene switching.
******************************************************************************/

// Helper headers
#include "globals.hpp"
#include "fonts.hpp" // Preload fonts

// Game scenes
#include "scenes/menu.hpp"
#include "scenes/game.hpp"
#include "scenes/console.hpp"
#include "scenes/credits.hpp"
#include "scenes/congrats.hpp"
#include "scenes/pause.hpp"

// SFML headers
#include <SFML/Graphics.hpp>

// Core functionality
#include <unordered_map>
#include <variant>
#include <functional>

using namespace std;
using namespace sf;

int main()
{
    // Store links to the functions in each scene
    unordered_map<string, Scene> scenes = {
        {"menu", menu},
        {"credits", credits},
        {"game", game},
        {"console", console},
        {"congrats", congrats},
        {"pause", pause}
    };
    
    // Store global data
    globals data {
        .curScene = "menu",
        .windowSize = {640, 640},
        .gridSize = {10, 10},
        .tileSize = 64
    };
    
    string activeScene = "";

    // Create window
    RenderWindow window(
        VideoMode(data.windowSize),     // Window resolution
        "Textra Errestrial",            // Window title
        Style::Titlebar | Style::Close  // Window features
    );
    window.setFramerateLimit(144);      // Max FPS
    
    // Main window loop
    while (window.isOpen())
    {
        // If we've switched scenes, call the appropriate functions
        if (data.curScene != activeScene)
        {
            scenes[activeScene].end(data, window);
            activeScene = data.curScene;
            scenes[activeScene].start(data, window);
        }

        // Loop through each event
        while (const optional event = window.pollEvent())
        {
            // If it's a closure event, close the window
            if (event -> is<Event::Closed>())
            {
                window.close();
            }
            
            // Otherwise, send it to the current scene
            scenes[activeScene].handleInput(data, window, *event);
        }
        
        window.clear();
        scenes[activeScene].render(data, window);
        window.display();
    }
}