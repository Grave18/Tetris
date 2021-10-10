#pragma once

#include <raylib.h>

// Minimal part of the level
class Tile
{
public:
	Tile(int x = 0, int y = 0, Color color = BLACK)
		: x_(x), y_(y), color_(color)
	{
	}

	Color getColor() const
	{
		return color_;
	}

private:
	int x_, y_;
	Color color_; 
};
