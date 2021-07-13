#pragma once

#include <raylib.h>
#include <vector>

#include "rectangle.h"
#include "figure_enum.h"

// Представляет собой фигуру, которой управляет игрок
class Figure
{
public:
	int size;
	FigureEnum figure_type;

private:
	std::vector<Rec> recs;

public:
	Figure();

	Figure(std::vector<Rec> rectangles, FigureEnum type, Color color = BLACK, Color outline_color = BLACK);

	Rec& operator[](unsigned int index);
	const Rec& operator[](unsigned int index) const;
};
