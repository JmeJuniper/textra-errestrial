/******************************************************************************
 * main.cpp
 * Main source file
 * Sets up SFML window, handles basic scene switching.
******************************************************************************/

// Helper headers
#include "dataType.hpp"

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

// Function to retrieve the current scene
Scene getCurScene(unordered_map<string, Scene> &scenes, dataType &data) {
    // 1. Retrieve the "curScene" from data as a string (data uses a variant class to store values)
    // 2. Use the current scene to index scenes for a referenceWrapper pointing to the proper scene
    // 3. Get the original object from the referenceWrapper
    // 4. Return the value
    return scenes[get<string>(data["curScene"])];
};

int main()
{
    // Store links to the functions in each scene
    unordered_map<string, Scene>
    scenes = {
        {"menu", menu}
    };
    
    // Store global data
    dataType data = {
        {"curScene", "menu"}
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
                getCurScene(scenes, data).handleInput(data, window, event.value());
            }
        }
        
        window.clear();
        getCurScene(scenes, data).render(data, window);
        window.display();
    }
}