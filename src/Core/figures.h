#pragma once

#include <array>
#include <raylib.h>

#include <tile.h>

class Figures
{
public:
	static std::array<Tile, 4> o;
	static std::array<Tile, 4> i;
};

std::array<Tile, 4> Figures::o
{ 
	{{ 0, 0, YELLOW }, { 0, 1, YELLOW }, { 1, 0, YELLOW }, { 1, 1, YELLOW }} 
};

std::array<Tile, 4> Figures::i
{
	{{0, -2, SKYBLUE }, { 0,-1, SKYBLUE }, { 0, 0, SKYBLUE}, { 0, 1, SKYBLUE }}
};