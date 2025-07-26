/******************************************************************************
 * Player.hpp
 * Header file for Player.cpp
 * Class for a player that can move.
 * Defines Player class (inherits Object)
 * * offMap [bool]
 * * * True if the player just moved off the map.
******************************************************************************/

#ifndef PLAYER_H
    #define PLAYER_H
    
    #include <SFML/Graphics.hpp>
    #include "game/objects/Object.hpp"
    
    class Map;
    
    class Player: public Object {
        public:
        
        // Inherit constructor
        using Object::Object;
        
        // Attempts to move in a direction, returns a bool corresponding to success
		// diff     [Vector2i] - Direction to move in. I.e. {-1, 0} = move 1 to the left.
		// <-           [bool] - True if object successfully moved, false if not.
        bool tryMove(sf::Vector2i diff) override;
        
        // True if the player just moved off the map
        bool offMap = false;
    };
#endif