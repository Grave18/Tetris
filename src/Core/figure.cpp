#include "figure.h"

Figure::Figure()
	: figure_type{ } {}

Figure::Figure(std::array<Rec, 4> rectangles, Figures type, Color color, Color outline_color)
: figure_type{ type }, recs_{ rectangles }
{
	size = recs_.size();

	for (auto& rec : recs_)
	{
		rec.color = color;
		rec.outline_color = outline_color;
	}
}

const Figure Figure::o{ std::array<Rec, 4>{{ { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } }}, Figures::O, YELLOW };
const Figure Figure::i{ std::array<Rec, 4>{{ { 0,-2 }, { 0,-1 }, { 0, 0 }, { 0, 1 } }}, Figures::I, SKYBLUE };
const Figure Figure::s{ std::array<Rec, 4>{{ {-1, 0 }, { 0,-1 }, { 0, 0 }, { 1,-1 } }}, Figures::S, RED };
const Figure Figure::z{ std::array<Rec, 4>{{ {-1,-1 }, { 0,-1 }, { 0, 0 }, { 1, 0 } }}, Figures::Z, GREEN };
const Figure Figure::l{ std::array<Rec, 4>{{ { 0,-1 }, { 0, 0 }, { 0, 1 }, { 1, 1 } }}, Figures::L, ORANGE };
const Figure Figure::j{ std::array<Rec, 4>{{ {-1, 1 }, { 0,-1 }, { 0, 0 }, { 0, 1 } }}, Figures::J, PINK };
const Figure Figure::t{ std::array<Rec, 4>{{ {-1, 0 }, { 0,-1 }, { 0, 0 }, { 1, 0 } }}, Figures::T, PURPLE };

Rec& Figure::operator[](uint64_t index)
{
	return recs_[index];
}

const Rec& Figure::operator[](uint64_t index) const
{
	return recs_[index];
}