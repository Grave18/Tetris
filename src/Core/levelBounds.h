#pragma once

// Left to right up to down bounds an size of a tile size
struct LevelBounds
{
	int levelToScreenPosX;
	int levelToScreenPosY;
	int width;
	int height;
	int tileSize;
};