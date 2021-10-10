#pragma once

#include <raylib.h>
#include "tile.h"
#include "levelBounds.h"

// Provide rendering of a tile
class Graphics
{
public:
	Graphics(const LevelBounds& bounds)
		: bounds_(bounds)
		, rec_{0, 0, static_cast<float>(bounds.tileSize), static_cast<float>(bounds.tileSize)}
	{ }

	void drawLevelFrame(int frameWidth = 5, int frameOffset = 5)
	{
		// draw level frame
		
		Rectangle worldBoundFrame{
			static_cast<float>(bounds_.levelToScreenPosX - frameOffset),
			static_cast<float>(bounds_.levelToScreenPosY - frameOffset),
			static_cast<float>(bounds_.width * bounds_.tileSize + frameOffset * 2),
			static_cast<float>(bounds_.height * bounds_.tileSize + frameOffset * 2) };

		float roundness = 0.07f;
		DrawRectangleRounded(worldBoundFrame, roundness, frameWidth, LIGHTGRAY);
		DrawRectangleRoundedLines(worldBoundFrame, roundness, 1, frameWidth, RED);
	}

	void drawTile(const Tile& tile)
	{
		rec_.x = static_cast<float>(bounds_.levelToScreenPosX + tile.getX() * bounds_.tileSize);
		rec_.y = static_cast<float>(bounds_.levelToScreenPosY + tile.getY() * bounds_.tileSize);
		DrawRectangleRounded(rec_, 0.5f, 1, tile.getColor());
		DrawRectangleRoundedLines(rec_, 0.5f, 1, bounds_.tileSize / 15, BLACK);
	}

private:
	Rectangle rec_;
	const LevelBounds bounds_;
};