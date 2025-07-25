/******************************************************************************
 * Console.hpp
 * Header file for Console.cpp
 * Class for consoles that block movement but display a screen on interaction.
 * Documentation inherits from Object.hpp
******************************************************************************/

#ifndef CONSOLE_H
    #define CONSOLE_H
    
    #include <SFML/Graphics.hpp>
    #include "game/objects/Object.hpp"
    
    class Console: public Object {
        public:
        
		// Name of the image displayed on the console
        std::string img;
        
        // True when the player walks into the console
        bool interacted = false;
        
        // Inherit constructor
        using Object::Object;

        // tryMove overriden for Walls
        bool tryMove(sf::Vector2i diff) override;
    };
#endif