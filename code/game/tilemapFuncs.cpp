/******************************************************************************
 * tilemapFuncs.cpp
 * Source file for tilemapFuncs.hpp
 * Functions for reading tilemaps and converting them to Maps of Objects.
******************************************************************************/

#include "game/tilemapFuncs.hpp"

std::unordered_map<char, std::string> cttl = {
	// Walls
	{'/', "wall_0_0.png"},
	{'-', "wall_1_0.png"},
	{'\\', "wall_2_0.png"},
	{'[', "wall_0_1.png"},
	{'X', "wall_1_1.png"},
	{']', "wall_2_1.png"},
	{'L', "wall_0_2.png"},
	{'_', "wall_1_2.png"},
	{'!', "wall_2_2.png"},
	{'.', "corner_0_1.png"},
	{',', "corner_1_1.png"},
	{'=', "console.png"},
	
	// Floors
	{' ', "tile.png"},
	{'o', "button.png"}
};