/******************************************************************************
 * Scene.hpp
 * Solo header file
 
 
 * Defines Scene class:
 
 * * Scene.handleInput()
 * * * Parameters:
 * * * * data [globals&]
 * * * * * Mutable reference to global game data.
 * * * * window [sf::RenderWindow&]
 * * * * * Mutable reference to the window to render the scene to.
 * * * * event [const sf::Event&]
 * * * * * Immutable reference to the SFML event data.
 * * * Return:
 * * * * void
 * * * Description:
 * * * * Handles SFML input events
 
 * * Scene.start()
 * * * Parameters:
 * * * * data [globals&]
 * * * * * Mutable reference to global game data.
 * * * * window [sf::RenderWindow&]
 * * * * * Mutable reference to the window to render the scene to.
 * * * Return:
 * * * * void
 * * * Description:
 * * * * Run when the scene is switched to.
 
 * * Scene.render()
 * * * Parameters:
 * * * * data [globals&]
 * * * * * Mutable reference to global game data.
 * * * * window [sf::RenderWindow&]
 * * * * * Mutable reference to the window to render the scene to.
 * * * Return:
 * * * * void
 * * * Description:
 * * * * Handles the update loop and renders to the screen.
 
 * * Scene.end()
 * * * Parameters:
 * * * * data [globals&]
 * * * * * Mutable reference to global game data.
 * * * * window [sf::RenderWindow&]
 * * * * * Mutable reference to the window to render the scene to.
 * * * Return:
 * * * * void
 * * * Description:
 * * * * Run when the scene is switched away from.
******************************************************************************/

#ifndef SCENE_H
    #define SCENE_H
    
    #include "globals.hpp"
    #include <SFML/Graphics.hpp>
    #include <functional>
    #include <optional>
    
    // Types for the defined functions
    using InputHandler = std::function<void(globals&, sf::RenderWindow&, const sf::Event&)>;
    using Misc = std::function<void(globals&, sf::RenderWindow&)>;
    
    // Define the scene class
    class Scene
    {
        public:
        
        // Assign functions
        Scene
        (
            // Input handler
            InputHandler ih = [](globals& data, sf::RenderWindow& window, const sf::Event& event){},
            
            // Scene enter
            Misc s = [](globals& data, sf::RenderWindow& window){},

            // Renderer
            Misc r = [](globals& data, sf::RenderWindow& window){},

            // Scene exit
            Misc e = [](globals& data, sf::RenderWindow& window){}
        ): handleInput(ih), start(s), render(r), end(e) {};
        
        // Empty functions, to be overwritten per instance
        InputHandler handleInput;
        Misc render, start, end;
    };

#endif