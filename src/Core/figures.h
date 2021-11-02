#pragma once

#include <array>
#include <raylib.h>
#include <tile.h>

class Figures
{
	using Figure = std::array<Tile, 4>;

public:
	static Figure o;
	static Figure i;
	static Figure s;
	static Figure z;
	static Figure l;
	static Figure j;
	static Figure t;
};