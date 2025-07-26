/******************************************************************************
 * Comms.hpp
 * Header file for Comms.cpp
 * Class for consoles that block movement but display an interactive screen.
 * Documentation inherits from Object.hpp
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

        // tryMove overriden for Walls
        bool tryMove(sf::Vector2i diff) override;
    };
#endif