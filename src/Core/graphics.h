#pragma once

#include <raylib.h>
#include "tile.h"

class Graphics
{
public:
	Graphics(int sectorSize)
		: sectorSize_(sectorSize)
		,rec{ 0 , 0, static_cast<float>(sectorSize), static_cast<float>(sectorSize) }
	{}

	void drawTile(const Tile& tile, int x = 0, int y = 0)
	{
		rec.x = x * sectorSize_;
		rec.y = y * sectorSize_;
		DrawRectangleRounded(rec, 0.5f, 1, tile.getColor());
		DrawRectangleRoundedLines(rec, 0.5f, 1, 3, BLACK);
	}

private:
	Rectangle rec;
	int sectorSize_;
};