#pragma once

#include <raylib.h>
#include "tile.h"
#include "levelBounds.h"

// Provide rendering of a tile
class Graphics
{
public:
	explicit Graphics(const LevelBound& bounds)
		: bounds_(bounds)
		
	{ }

	void drawLevelBackground(int frameWidth = 5, int frameOffset = 5) const
	{
		// draw level background and frame
		Rectangle levelBound
		{
			static_cast<float>(bounds_.levelToScreenPosX - frameOffset),
			static_cast<float>(bounds_.levelToScreenPosY - frameOffset),
			static_cast<float>(bounds_.width * bounds_.tileSize + frameOffset * 2),
			static_cast<float>(bounds_.height * bounds_.tileSize + frameOffset * 2) 
		};

		float roundness = 0.07f;
		DrawRectangleRounded(levelBound, roundness, frameWidth, LIGHTGRAY);
		DrawRectangleRoundedLines(levelBound, roundness, 1, frameWidth, RED);
	}

	void drawTile(const Tile& tile, int worldX = 0, int worldY = 0) const
	{
		if (worldY + tile.getY() >= 0)
		{
			Rectangle tileRec
			{
				static_cast<float>(bounds_.levelToScreenPosX + (worldX + tile.getX()) * bounds_.tileSize),
				static_cast<float>(bounds_.levelToScreenPosY + (worldY + tile.getY()) * bounds_.tileSize),
				static_cast<float>(bounds_.tileSize),
				static_cast<float>(bounds_.tileSize)
			};

			float roundness = 0.5f;
			int lineThick = bounds_.tileSize / 15;
			DrawRectangleRounded(tileRec, roundness, 1, tile.getColor());
			DrawRectangleRoundedLines(tileRec, roundness, 1, lineThick, BLACK);
		}
	}

private:
	const LevelBound bounds_;
};