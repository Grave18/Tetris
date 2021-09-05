#pragma once

#include "rectangle.h"

Rec::Rec(const int x, const int y, Color color, Color outline_color) // x = 0, y = 0, color = BLACK, outline_color = BLACK
	: x{ x }, y{ y }, is_occupied{ false }, color{ color }, outline_color{ outline_color } {}

void Rec::clear()
{
	x = 0;
	y = 0;
	is_occupied = false;
	color = BLACK;
	outline_color = BLACK;
}
