/******************************************************************************
 * tilemapUtils.hpp
 * Header file for tilemapUtils.cpp
 * Utilities for reading tilemaps and converting them to Maps of Objects.
 * 
 * cttl [std::unordered_map]:
 * * Key [char]:
 * * * A character representing the tilemap object.
 * * Value [std::pair]:
 * * * First [std::string]:
 * * * * The file name, including extension, of the sprite correpsonding to the
 * * * * object.
 * * * Seocond [char]:
 * * * * The type of object represented. F = Floor, W = Wall.
******************************************************************************/

#ifndef TILEMAPUTILS_H
    #define TILEMAPUTILS_H
    
    #include <unordered_map>
    #include <string>
    
    extern std::unordered_map<char, std::pair<std::string, char>> cttl;
#endif