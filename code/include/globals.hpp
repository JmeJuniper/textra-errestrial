/******************************************************************************
 * globals.hpp
 * Solo header file
 * Defines "globals" type alias for use in other files.
******************************************************************************/

#ifndef GLOBALS_H
    #define GLOBALS_H
    
    #include <string>
    #include <SFML/Graphics.hpp>
    
    // Struct to store global data
    struct globals {
        std::string curScene;
        std::string returnFromPause;
        sf::Vector2u windowSize;
        sf::Vector2i gridSize;
        int tileSize;
        std::string consoleImg;
    };

#endif