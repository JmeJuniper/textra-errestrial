/******************************************************************************
 * tilemapFuncs.cpp
 * Source file for tilemapFuncs.hpp
 * Functions for reading tilemaps and converting them to Maps of Objects.
******************************************************************************/

#include "game/tilemapFuncs.hpp"

std::unordered_map<char, std::pair<std::string, char>> cttl = {
	// Walls
	{'/', {"wall_0_0.png", 'W'}},
	{'-', {"wall_1_0.png", 'W'}},
	{'\\', {"wall_2_0.png", 'W'}},
	{'[', {"wall_0_1.png", 'W'}},
	{'X', {"wall_1_1.png", 'W'}},
	{']', {"wall_2_1.png", 'W'}},
	{'L', {"wall_0_2.png", 'W'}},
	{'_', {"wall_1_2.png", 'W'}},
	{'J', {"wall_2_2.png", 'W'}},
	{'.', {"corner_0_1.png", 'W'}},
	{',', {"corner_1_1.png", 'W'}},
	{'=', {"console.png", 'W'}},
	
	// Floors
	{' ', {"tile.png", 'F'}},
	{'o', {"button.png", 'F'}}
};