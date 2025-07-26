/******************************************************************************
 * game.cpp
 * Source file for game.hpp
 * Represents the main game scene
 * Impliments the handleInput, start, render, and end functions of the game scene
******************************************************************************/

#include <memory>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include "fonts.hpp"
#include "scenes/game.hpp"
#include "game/Map.hpp"
#include "game/objects/Player.hpp"
#include "game/objects/Box.hpp"
#include "game/objects/Console.hpp"
#include "game/objects/Comms.hpp"

using namespace sf;

namespace {
	// Store the entire tilemap
	Map map;
	
	// A shared pointer to the player, to access its functions
	std::shared_ptr<Player> player;
	
	// A vector of shared pointers to all consoles
	std::vector<std::shared_ptr<Console>> consoles;
	
	// A vector of shared pointers to the communications console
	std::vector<std::shared_ptr<Comms>> comms;

	// The position of the current map being viewed.
	sf::Vector2i curMapPos(1, 0);
	
	// Has the game been initialized yet?
	bool gameStarted = false;
}

void switchMap(globals &data) {
	// String for the folder to get map data from
	std::string dataLoc = "data/levels/" + std::to_string(curMapPos.x) + std::to_string(curMapPos.y) + "/";

	Vector2i playerPos;

	// If we're moving from a previous map:
	if (gameStarted)
	{
		// Get the position of the player
		playerPos = player -> pos;
		
		// Wrap player position if off-map
		while (playerPos.y < 0)
			playerPos.y += data.gridSize.y;
		while (playerPos.y >= data.gridSize.y)
			playerPos.y -= data.gridSize.y;
		while (playerPos.x < 0)
			playerPos.x += data.gridSize.x;
		while (playerPos.x >= data.gridSize.x)
			playerPos.x -= data.gridSize.x;
	}
	// Otherwise:
	else
	{
		playerPos = {8, 2};
	}

	// Create a new map, and load the appropriate tilemap
	map = Map();
	map.loadTilemap(data.gridSize.x, data.gridSize.y, dataLoc + "tilemap.txt");
	
	// Create new player at proper position
	player = map.place<Player>(playerPos.x, playerPos.y, "box.png");
	
	// Place consoles per consoles.txt
	consoles = {};
	
	std::ifstream consoleReader(dataLoc + "consoles.txt");
	size_t x, y;
	std::string img;
	
	while (consoleReader >> x >> y >> img)
	{
		auto newConsole = map.place<Console>(x, y, "console.png");
		newConsole -> img = "assets/images/consoles/" + img;
		consoles.push_back(std::move(newConsole));
	}
	
	consoleReader.close();
	
	// Place comms per comms.txt
	comms = {};
	
	std::ifstream commsReader(dataLoc + "comms.txt");
	while (commsReader >> x >> y)
		comms.push_back(map.place<Comms>(x, y, "console.png"));
	
	consoleReader.close();
	
	// Place boxes per boxes.txt
	std::ifstream boxReader(dataLoc + "boxes.txt");
	while (boxReader >> x >> y)
		map.place<Box>(x, y, "box.png");
	
	boxReader.close();
}

Scene game(
	// Input Handler
	[](globals &data, RenderWindow &window, Event event)
	{
		// Get keyboard input
		if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>()) {
			// Move player on arrow keys, and change map if moved offscreen
			if (keyEvent -> code == sf::Keyboard::Key::Up)
			{
				player -> tryMove({ 0, -1});
				if (player -> offMap)
					curMapPos.y -= 1;
			}
			if (keyEvent -> code == sf::Keyboard::Key::Down)
			{
				player -> tryMove({ 0,  1});
				if (player -> offMap)
					curMapPos.y += 1;
			}
			if (keyEvent -> code == sf::Keyboard::Key::Left)
			{
				player -> tryMove({-1,  0});
				if (player -> offMap)
					curMapPos.x -= 1;
			}
			if (keyEvent -> code == sf::Keyboard::Key::Right)
			{
				player -> tryMove({ 1,  0});
				if (player -> offMap)
					curMapPos.x += 1;
			}

			// If the player is moved offscreen, the map needs to be switched
			if (player -> offMap)
				switchMap(data);
			
			// Check if the player interacted with a console
			for (auto c: consoles)
			{
				if (c -> interacted)
				{
					c -> interacted = false;
					data.curScene = "console";
					data.consoleImg = c -> img;
					break;
				}
			}
			
			// Check if the player interacted with a comms terminal
			for (auto c: comms)
			{
				if (c -> interacted)
				{
					c -> interacted = false;
					data.curScene = "comms";
					break;
				}
			}
		}
	},
	
	// Scene enter
	[](globals &data, RenderWindow &window)
	{
		if (not gameStarted)
		{
			switchMap(data);
			gameStarted = true;
		}
	},
	
	// Renderer
	[](globals &data, RenderWindow &window)
	{
		map.draw(window, data.tileSize);
	},
	
	// Scene exit
	[](globals &data, RenderWindow &window)
	{
	
	}
);