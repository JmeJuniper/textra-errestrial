/******************************************************************************
 * Comms.hpp
 * Header file for Comms.cpp
 * Class for consoles that block movement but display an interactive screen.
 * Defines Comms class (inherits Object)
 * * interacted [bool]
 * * * True if the player just walked into the console.
******************************************************************************/

#ifndef COMMS_H
    #define COMMS_H
    
    #include <SFML/Graphics.hpp>
    #include "game/objects/Object.hpp"
    
    class Comms: public Object {
        public:
        
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