#pragma once

#include <raylib.h>

// ѕредставл€ет минимальную единицу - квадрат
class Rec
{
public:
	int x, y;
	Color color;
	Color outline_color;

	Rec();

	Rec(int x, int y, Color color = BLACK, Color outline_color = BLACK);
};
