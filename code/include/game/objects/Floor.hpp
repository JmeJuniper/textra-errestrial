/******************************************************************************
 * Floor.hpp
 * Solo header file
 * Class for tiles that do not move nor block movement.
 * Defines Floor class (inherits Object)
******************************************************************************/

#ifndef FLOOR_H
    #define FLOOR_H
    
    #include <SFML/Graphics.hpp>
    #include "game/objects/Object.hpp"
    
    class Floor: public Object {
        public:
        
        // Inherit constructor
        using Object::Object;
        
        // Attempts to move in a direction, returns a bool corresponding to success
		// diff     [Vector2i] - Direction to move in. I.e. {-1, 0} = move 1 to the left.
		// <-           [bool] - True if object successfully moved, false if not.
        bool tryMove(sf::Vector2i diff) override { return true; }
    };
#endif