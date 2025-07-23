/******************************************************************************
 * Floor.hpp
 * Solo header file
 * Class for tiles that do not move nor block movement.
******************************************************************************/

#ifndef FLOOR_H
    #define FLOOR_H
    
    #include <SFML/Graphics.hpp>
    #include "game/objects/Object.hpp"
    
    class Map;
    
    class Floor: public Object {
        public:
        
        // Inherit constructor
        using Object::Object;

        // tryMove overriden for Floors
        bool tryMove(sf::Vector2i diff) override { return true; }
    };
#endif