/******************************************************************************
 * Box.hpp
 * Header file for Box.cpp
 * Class for a box that can be pushed.
 * Defines Box class (inherits Object)
******************************************************************************/

#ifndef BOX_H
    #define BOX_H
    
    #include <SFML/Graphics.hpp>
    #include "game/objects/Object.hpp"
    
    class Box: public Object {
        public:
        
        // Inherit constructor
        using Object::Object;
        
        // Attempts to move in a direction, returns a bool corresponding to success
		// diff     [Vector2i] - Direction to move in. I.e. {-1, 0} = move 1 to the left.
		// <-           [bool] - True if object successfully moved, false if not.
        bool tryMove(sf::Vector2i diff) override;
    };
#endif