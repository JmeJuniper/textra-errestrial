/******************************************************************************
 * Console.hpp
 * Header file for Console.cpp
 * Class for consoles that block movement but display a screen on interaction.
 * Defines Console class (inherits Object)
 * * img [std::string]
 * * * Filename (including extension) of the image to display when the console
 * * * is opened.
 * * interacted [bool]
 * * * True if the player just walked into the console.
******************************************************************************/

#ifndef CONSOLE_H
    #define CONSOLE_H
    
    #include <SFML/Graphics.hpp>
    #include "game/objects/Object.hpp"
    
    class Console: public Object {
        public:
        
		// Name of the image displayed on the console
        std::string img;
        
        // True when the player walks into the console
        bool interacted = false;
        
        // Inherit constructor
        using Object::Object;
        
        // Attempts to move in a direction, returns a bool corresponding to success
		// diff     [Vector2i] - Direction to move in. I.e. {-1, 0} = move 1 to the left.
		// <-           [bool] - True if object successfully moved, false if not.
        bool tryMove(sf::Vector2i diff) override;
    };
#endif