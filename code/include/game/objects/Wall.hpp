/******************************************************************************
 * Wall.hpp
 * Solo header file
 * Class for tiles that do not move but block movement.
 * Documentation inherits from Object.hpp
******************************************************************************/

#ifndef WALL_H
    #define WALL_H
    
    #include <SFML/Graphics.hpp>
    #include "game/objects/Object.hpp"
    
    class Wall: public Object {
        public:
        
        // Inherit constructor
        using Object::Object;
        
        // tryMove overriden for Walls
        bool tryMove(sf::Vector2i diff) override { return false; }
    };
#endif