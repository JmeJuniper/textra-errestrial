/******************************************************************************
 * scene.hpp
 * Solo header file
 
 
 * Defines Scene class:
 
 * * Scene.handleInput()
 * * * Parameters:
 * * * * data
 * * * * * Type - reference to dataType
 * * * * * Contains global game data
 * * * * event
 * * * * * Type - sf::Event
 * * * * * Contains event information
 * * * Return:
 * * * * void
 * * * Description:
 * * * * Handles SFML input events
 
 * * Scene.render()
 * * * Parameters:
 * * * * data
 * * * * * Type - reference to dataType
 * * * * * Contains global game data
 * * * Return:
 * * * * void
 * * * Description:
 * * * * Handles the update loop and renders to the screen.
******************************************************************************/

#ifndef SCENE_H
    #define SCENE_H
    
    #include "dataType.hpp"
    #include <SFML/Graphics.hpp>
    #include <functional>

    using namespace std;
    
    // Types for the defined functions
    using InputHandler = function<void(dataType&, sf::RenderWindow&, sf::Event)>;
    using Renderer = function<void(dataType&, sf::RenderWindow&)>;
    
    // Define the scene class
    class Scene
    {
        public:
        
        // Assign functions
        Scene
        (
            InputHandler ih = [](dataType& data, sf::RenderWindow &window, sf::Event event){},
            Renderer r = [](dataType& data, sf::RenderWindow &window){}
        )
        {
            handleInput = ih;
            render = r;
        };
        
        // Empty functions, to be overwritten per instance
        InputHandler handleInput;
        Renderer render;
    };

#endif