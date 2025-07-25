/******************************************************************************
 * Box.hpp
 * Header file for Box.cpp
 * Class for a box that can be pushed.
 * Documentation inherits from Object.hpp
******************************************************************************/

#ifndef BOX_H
    #define BOX_H
    
    #include <SFML/Graphics.hpp>
    #include "game/objects/Object.hpp"
    
    class Map;
    
    class Box: public Object {
        public:
        
        // Inherit constructor
        using Object::Object;
        
        // tryMove overriden for Boxes
        bool tryMove(sf::Vector2i diff) override;
    };
#endif