/******************************************************************************
 * dataType.hpp
 * Solo header file
 * Defines "dataType" type alias for use in other files.
******************************************************************************/

#ifndef DATATYPE_H
    #define DATATYPE_H
    
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