/******************************************************************************
 * Object.hpp
 * Header file for Object.cpp
 * Superclass of all objects that go on the tilemap
 * 
 * Defines Object class:
 * * Constructor
 * * * Parameters
 * * * * spriteName [string]
 * * * * * The filename of the sprite to use.
******************************************************************************/

#ifndef OBJECT_H
	#define OBJECT_H
	
	#include <SFML/Graphics.hpp>
	
	class Map;
	
	class Object {
		public:
		// Constructor
		// spriteName [string] - File name of sprite, including extension.
		// initPos  [Vector2i] - Starting position
		// mapLink      [Map&] - Reference to the containing Map object
		// gridSize      [int] - Size of grid, in pixels
		Object(std::string spriteName, sf::Vector2i initPos, Map* mapLink);

		// Destructor
		virtual ~Object() = default;
		
		// Position of object
		sf::Vector2i pos;

		// Attempts to move in a direction, returns a bool corresponding to success
		// diff     [Vector2i] - Direction to move in. I.e. {-1, 0} = move 1 to the left.
		// <-           [bool] - True if object successfully moved, false if not.
		virtual bool tryMove(sf::Vector2i diff);

		void draw(sf::RenderWindow& window, size_t x, size_t y, unsigned int tileSize);
		
		private:
		// Reference to parent Map
		Map* map;
		
		// Object sprite and texture
		sf::Texture tex;
		sf::Sprite spr;
	};
#endif