#include "figure.h"

Figure::Figure()
	: recs{ }, figure_type{ } {}

Figure::Figure(std::vector<Rec> rectangles, FigureEnum type, Color color, Color outline_color) //color = BLACK, outline_color = BLACK
	: recs{ rectangles }, figure_type{ type }
{
	size = recs.size();

	for (int i = 0; i < recs.size(); ++i)
	{
		recs[i].color = color;
		recs[i].outline_color = outline_color;
	}
}

Rec& Figure::operator[](unsigned int index)
{
	return recs[index];
}

const Rec& Figure::operator[](unsigned int index) const
{
	return recs[index];
}