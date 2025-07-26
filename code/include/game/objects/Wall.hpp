/******************************************************************************
 * Wall.hpp
 * Solo header file
 * Class for tiles that do not move but block movement.
 * Defines Wall class (inherits Object)
******************************************************************************/

#ifndef WALL_H
    #define WALL_H
    
    #include <SFML/Graphics.hpp>
    #include "game/objects/Object.hpp"
    
    class Wall: public Object {
        public:
        
        // Inherit constructor
        using Object::Object;
        
        // Attempts to move in a direction, returns a bool corresponding to success
		// diff     [Vector2i] - Direction to move in. I.e. {-1, 0} = move 1 to the left.
		// <-           [bool] - True if object successfully moved, false if not.
        bool tryMove(sf::Vector2i diff) override { return false; }
    };
#endif