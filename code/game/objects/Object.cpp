/******************************************************************************
 * Object.cpp
 * Source file for Object.hpp
 * Superclass of all objects that go on the tilemap
******************************************************************************/

#include "game/objects/Object.hpp"
#include <SFML/Graphics.hpp>

Object::Object
(
    std::string spriteName,
    sf::Vector2i initPos,
    Map* mapLink
): pos(initPos), map(mapLink), tex("assets\\sprites\\" + spriteName), spr(tex)
{
    spr.setTexture(tex);
}

void Object::draw(sf::RenderWindow& window, unsigned int tileSize)
{
    // Resize sprite to be exactly 1 grid size and positioned properly
    spr.setScale(sf::Vector2f(
        tileSize / static_cast<float>(tex.getSize().x),
        tileSize / static_cast<float>(tex.getSize().y)
    ));
    spr.setPosition(static_cast<sf::Vector2f>(pos) * static_cast<float>(tileSize));
    
    window.draw(spr);
}