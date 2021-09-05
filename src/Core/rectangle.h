#pragma once

#include <raylib.h>

// Представляет собой квадрат - минимальную частицу мира
class Rec
{
public:
	int x, y;
	bool is_occupied;
	Color color;
	Color outline_color;

	Rec(int x = 0, int y = 0, Color color = BLACK, Color outline_color = BLACK);

	void clear();
};
