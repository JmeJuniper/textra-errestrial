/******************************************************************************
 * MenuItem.cpp
 * Source file for MenuItem.hpp
 * Struct and helper function for setting up rect-bounded text elements
******************************************************************************/

#include "menu/MenuItem.hpp"

MenuItem::MenuItem
(
    const std::string& text,
    float x,
    float y,
    const sf::Font& font,
    callbackFun onClick,
    bool small
): box({200, 50}), label(font, text), callback(onClick)
{
    if (small)
        box.setSize({50, 50});
    box.setPosition({x, y});
    box.setFillColor(sf::Color(70, 70, 70));
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(2);
    
    label.setCharacterSize(small? 50 : 24);
    label.setFillColor(sf::Color::White);
    label.setPosition({x + (small? 10 : 20), y + (small? -5 : 10)});
}