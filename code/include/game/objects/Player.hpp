/******************************************************************************
 * Player.hpp
 * Header file for Player.cpp
 * Class for a player that can move.
 * Documentation inherits from Object.hpp
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
        
        // tryMove overriden for Players
        bool tryMove(sf::Vector2i diff) override;
    };
#endif