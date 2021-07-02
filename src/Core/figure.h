#pragma once

#include <raylib.h>
#include <vector>

#include "rectangle.h"

// Представляет фигуру
class Figure
{
public:
	std::vector<Rec> recs;
	int size;

	Figure();

	Figure(std::vector<Rec> rectangles, Color color = BLACK, Color outline_color = BLACK);
};
