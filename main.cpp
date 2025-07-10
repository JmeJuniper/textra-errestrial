/******************************************************************************
 * main.cpp
 * Main source file
 * Sets up SFML window, handles basic scene switching.
******************************************************************************/

// Helper headers
#include "globals.hpp"

// Game scenes
#include "scenes/menu.hpp"

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
    unordered_map<string, Scene>
    scenes = {
        {"menu", menu}
    };
    
    // Store global data
    globals data {
        .curScene = "menu"
    };
    
    // Create window
    RenderWindow window(
        VideoMode({640, 640}),          // Window resolution
        "Textra Errestrial",            // Window title
        Style::Titlebar | Style::Close  // Window features
    );
    window.setFramerateLimit(144);      // Max FPS
    
    // Main window loop
    while (window.isOpen())
    {
        // Loop through each event
        while (const optional event = window.pollEvent())
        {
            // If it's a closure event, close the window
            if (event -> is<Event::Closed>())
            {
                window.close();
            }
            
            // Otherwise, send it to the current scene
            else if (event.has_value())
            {
                scenes[data.curScene].handleInput(data, window, event.value());
            }
        }
        
        window.clear();
        scenes[data.curScene].render(data, window);
        window.display();
    }
}