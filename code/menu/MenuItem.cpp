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
    callbackFun onClick
): box({200, 50}), label(font, text), callback(onClick)
{
    box.setPosition({x, y});
    box.setFillColor(sf::Color(70, 70, 70));
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(2);
    
    label.setCharacterSize(24);
    label.setFillColor(sf::Color::White);
    label.setPosition({x + 20, y + 10});
}