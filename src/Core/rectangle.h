#pragma once

#include <raylib.h>

// Представляет собой квадрат - минимальную частицу мира
class Rectangle
{
public:
	Rectangle(int x, int y, Color color)
		: x_(x), y_(y), color_(color)
	{
	}

private:
	int x_, y_;
	Color color_;
};
