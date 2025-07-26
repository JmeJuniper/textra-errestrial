/******************************************************************************
 * Object.hpp
 * Header file for Object.cpp
 * Superclass of all objects that go on the tilemap
 * 
 * Defines Object class:
 * * Constructor
 * * * Parameters
 * * * * spriteName [std::string]
 * * * * * File name of sprite, including extension.
 * * * * initPos [sf::Vector2i]
 * * * * * Starting position.
 * * * * mapLink [Map*]
 * * * * * Pointer to the containing Map object.
 * * pos [sf::Vector2i]
 * * * Current position of the object.
 * * tryMove
 * * * Parameters
 * * * * diff [sf::Vector2i]
 * * * * * Direction to move in. I.e. {-1, 0} = move 1 to the left.
 * * * Return [bool]
 * * * * True if object successfully moved, false if not.
 * * draw
 * * * Parameters
 * * * * window [sf::RenderWindow&]
 * * * * * Reference to the window to draw the object on.
 * * * * tileSize [unsigned int]
 * * * * * Size, in pixels, of each tile (1:1 aspect ratio assumed)
 * * * Return [void]
******************************************************************************/

#ifndef OBJECT_H
	#define OBJECT_H
	
	#include <SFML/Graphics.hpp>
	
	class Map;
	
	class Object {
		public:
		// Constructor
		// spriteName  [std::string] - File name of sprite, including extension.
		// initPos    [sf::Vector2i] - Starting position
		// mapLink            [Map*] - Pointer to the containing Map object
		Object(std::string spriteName, sf::Vector2i initPos, Map* mapLink);

		// Destructor
		virtual ~Object() = default;
		
		// Position of object
		sf::Vector2i pos;
		
		// Attempts to move in a direction, returns a bool corresponding to success
		// diff           [Vector2i] - Direction to move in. I.e. {-1, 0} = move 1 to the left
		// <-                 [bool] - True if object successfully moved, false if not
		virtual bool tryMove(sf::Vector2i diff);
		
		// Draws the sprite to the window
		// window [sf::RenderWindow] - Window to draw the object to
		// tileSize   [unsigned int] - Size of the tile, in pixels
		void draw(sf::RenderWindow& window, unsigned int tileSize);
		
		protected:
		// Reference to parent Map
		Map* map;
		
		// Object sprite and texture
		sf::Texture tex;
		sf::Sprite spr;
	};
#endif