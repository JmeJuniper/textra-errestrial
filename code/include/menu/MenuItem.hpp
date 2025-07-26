/******************************************************************************
 * MenuItem.hpp
 * Header file for MenuItem.cpp
 * Struct and helper function for setting up rect-bounded text elements
 * * MenuItem
 * * * Constructor
 * * * * Parameters
 * * * * * text [std::string]
 * * * * * * Text inside the button
 * * * * * x [float]
 * * * * * * x position of the button
 * * * * * y [float]
 * * * * * * y position of the button
 * * * * * font [sf::Font]
 * * * * * * SFML font to use to render the text
 * * * * * onClick [function]
 * * * * * * A function called when the button is pressed
 * * * * * * * Parameters
 * * * * * * * * globals&
 * * * * * * * * * Stores a reference to the data variable defined in main.cpp
 * * * * * * * * sf::RenderWindow&
 * * * * * * * * * Stores a reference to the program's window
 * * * * * * * Return [void]
 * * * * Return [MenuItem]
 * * * * * Returns the MenuItem class constructed with this.
******************************************************************************/

#ifndef MENUITEM_H
    #define MENUITEM_H
    
    #include <SFML/Graphics.hpp>
    #include <functional>
    #include "globals.hpp"
    
    using callbackFun = std::function<void(globals&, sf::RenderWindow&)>;
    
    struct MenuItem {
        sf::RectangleShape box;
        sf::Text label;
        callbackFun callback;
        
        MenuItem(const std::string& text, float x, float y, const sf::Font& font, callbackFun onClick, bool small = false);
    };

#endif