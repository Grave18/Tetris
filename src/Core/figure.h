#pragma once

#include <raylib.h>
#include <array>

#include "rectangle.h"

// Представляет собой фигуру, которой управляет игрок
class Figure
{
private:
	std::array<Rec, 4> recs_;

public:
	enum Figures
	{
		O, I, S, Z, L, J, T, MAX_ELEMENT
	};
	
	uint64_t size{};
	Figures figure_type;

	static const Figure o;
	static const Figure i;
	static const Figure s;
	static const Figure z;
	static const Figure l;
	static const Figure j;
	static const Figure t;

	Figure();
	Figure(std::array<Rec, 4> rectangles, Figures type, Color color = BLACK, Color outline_color = BLACK);

	Rec& operator[](uint64_t index);
	const Rec& operator[](uint64_t index) const;
};
