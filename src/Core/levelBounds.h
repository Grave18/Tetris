#pragma once

// Left to right up to down bounds an size of a tile size
struct LevelBound
{
	int windowToScreenPosX;
	int windowToScreenPosY;
	int windowWidthInTiles;
	int windowHeightInTiles;
	int tileSize;
};

struct ScoreBound
{
	int windowToScreenPosX;
	int windowToScreenPosY;
	int windowWidth;
	int windowHeight;
	int scorePositionX;
	int scorePositionY;
};