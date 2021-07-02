#include "figure.h"

Figure::Figure()
	: recs{ 0 } {}

Figure::Figure(std::vector<Rec> rectangles, Color color, Color outline_color) //Color color = BLACK, Color outline_color = BLACK
	: recs{ rectangles }
{
	size = recs.size();

	for (int i = 0; i < recs.size(); ++i)
	{
		recs[i].color = color;
		recs[i].outline_color = outline_color;
	}
}