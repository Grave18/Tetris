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
		, rec_{0, 0, static_cast<float>(bounds.tileSize), static_cast<float>(bounds.tileSize)}
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

	void drawTile(const Tile& tile, int worldX = 0, int worldY = 0)
	{
		if (worldY + tile.getY() >= 0)
		{
			rec_.x = static_cast<float>(bounds_.levelToScreenPosX + (worldX + tile.getX()) * bounds_.tileSize);
			rec_.y = static_cast<float>(bounds_.levelToScreenPosY + (worldY + tile.getY()) * bounds_.tileSize);
			DrawRectangleRounded(rec_, 0.5f, 1, tile.getColor());
			DrawRectangleRoundedLines(rec_, 0.5f, 1, bounds_.tileSize / 15, BLACK);
		}
	}

private:
	const LevelBound bounds_;
	Rectangle rec_;
};