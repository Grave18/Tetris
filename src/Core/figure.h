#pragma once

#include <raylib.h>
#include <array>

#include "rectangle.h"
#include "figure_enum.h"

// Представляет собой фигуру, которой управляет игрок
class Figure
{
public:
	int size;
	FigureEnum figure_type;

private:
	std::array<Rec, 4> recs;

public:
	Figure();

	Figure(std::array<Rec, 4> rectangles, FigureEnum type, Color color = BLACK, Color outline_color = BLACK);

	Rec& operator[](unsigned int index);
	const Rec& operator[](unsigned int index) const;
};
