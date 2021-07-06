#pragma once

#include <raylib.h>
#include <vector>

#include "rectangle.h"

// Представляет фигуру
class Figure
{
public:
	int size;

private:
	std::vector<Rec> recs;

public:
	Figure();

	Figure(std::vector<Rec> rectangles, Color color = BLACK, Color outline_color = BLACK);

	Rec& operator[](unsigned int index);
};
