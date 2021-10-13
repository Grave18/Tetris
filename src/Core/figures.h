#pragma once

#include <array>
#include <raylib.h>

#include <tile.h>

class Figures
{
public:
	static std::array<Tile, 4> o;
	static std::array<Tile, 4> i;
	static std::array<Tile, 4> s;
	static std::array<Tile, 4> z;
	static std::array<Tile, 4> l;
	static std::array<Tile, 4> j;
	static std::array<Tile, 4> t;
};

std::array<Tile, 4> Figures::o
{ 
	{{ 0, 0, YELLOW }, { 0, 1, YELLOW }, { 1, 0, YELLOW }, { 1, 1, YELLOW }} 
};

std::array<Tile, 4> Figures::i
{
	{{0, -2, SKYBLUE }, { 0,-1, SKYBLUE }, { 0, 0, SKYBLUE}, { 0, 1, SKYBLUE }}
};

std::array<Tile, 4> Figures::s
{
	{{-1, 0, RED }, { 0,-1, RED }, { 0, 0, RED }, { 1,-1, RED }}
};

std::array<Tile, 4> Figures::z
{
	{{-1,-1, GREEN }, { 0,-1, GREEN }, { 0, 0, GREEN }, { 1, 0, GREEN }}
};

std::array<Tile, 4> Figures::l
{
	{{ 0,-1, ORANGE }, { 0, 0, ORANGE }, { 0, 1, ORANGE }, { 1, 1, ORANGE }}
};

std::array<Tile, 4> Figures::j
{
	{{-1, 1, PINK }, { 0,-1, PINK }, { 0, 0, PINK }, { 0, 1, PINK }}
};

std::array<Tile, 4> Figures::t
{
	{{-1, 0, PURPLE }, { 0,-1, PURPLE }, { 0, 0, PURPLE }, { 1, 0, PURPLE }}
};