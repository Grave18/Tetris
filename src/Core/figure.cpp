#include "figure.h"

Figure::Figure()
	: figure_type{ } {}

Figure::Figure(std::array<Rec, 4> rectangles, figure_enum type, Color color, Color outline_color) //color = BLACK, outline_color = BLACK
	: figure_type{ type }, recs_{ rectangles }
{
	size = recs_.size();

	for (auto& rec : recs_)
	{
		rec.color = color;
		rec.outline_color = outline_color;
	}
}

Rec& Figure::operator[](unsigned int index)
{
	return recs_[index];
}

const Rec& Figure::operator[](unsigned int index) const
{
	return recs_[index];
}