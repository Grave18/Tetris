#include "figures.h"

std::array<Tile, 4> Figures::o
{
	{{ 0, -1, YELLOW }, { 1, -1, YELLOW }, { 0, 0, YELLOW }, { 1, 0, YELLOW }}
};

std::array<Tile, 4> Figures::i
{
	{{-1, 0, SKYBLUE }, { 0, 0, SKYBLUE }, { 1, 0, SKYBLUE}, { 2, 0, SKYBLUE }}
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
	{{ -1, -1, ORANGE }, { -1, 0, ORANGE }, { 0, 0, ORANGE }, { 1, 0, ORANGE }}
};

std::array<Tile, 4> Figures::j
{
	{{-1, -1, PINK }, { 0,-1, PINK }, { 1, -1, PINK }, { -1, 0, PINK }}
};

std::array<Tile, 4> Figures::t
{
	{{-1, 0, PURPLE }, { 0,-1, PURPLE }, { 0, 0, PURPLE }, { 1, 0, PURPLE }}
};