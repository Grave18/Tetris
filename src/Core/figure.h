#pragma once

#include <raylib.h>
#include <array>

#include "rectangle.h"
#include "figure_enum.h"

// Представляет собой фигуру, которой управляет игрок
class Figure
{
public:
	uint64_t size{};
	figure_enum figure_type;

private:
	std::array<Rec, 4> recs_;

public:
	Figure();

	Figure(std::array<Rec, 4> rectangles, figure_enum type, Color color = BLACK, Color outline_color = BLACK);

	Rec& operator[](unsigned int index);
	const Rec& operator[](unsigned int index) const;
};
