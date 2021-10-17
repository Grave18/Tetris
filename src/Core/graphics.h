#pragma once

#include <raylib.h>
#include <string>
#include "tile.h"
#include "levelBounds.h"

// Provide rendering of a tile
class GraphicsSystem
{
public:
	GraphicsSystem(const LevelBound& levelBounds, const ScoreBound& scoreBound)
		: levelBound_(levelBounds)
		, scoreBound_(scoreBound)
	{ }

	void drawLevelBackground() const
	{
		int frameOffset = 5;
		// draw level background and frame
		Rectangle levelBoundRec
		{
			static_cast<float>(levelBound_.windowToScreenPosX - frameOffset),
			static_cast<float>(levelBound_.windowToScreenPosY - frameOffset),
			static_cast<float>(levelBound_.windowWidthInTiles * levelBound_.tileSize + frameOffset * 2),
			static_cast<float>(levelBound_.windowHeightInTiles * levelBound_.tileSize + frameOffset * 2) 
		};

		int frameWidth = 5;
		float roundness = 0.07f;
		DrawRectangleRounded(levelBoundRec, roundness, 1, LIGHTGRAY);
		DrawRectangleRoundedLines(levelBoundRec, roundness, 1, frameWidth, RED);
	}

	void drawScore(int score) const
	{
		Rectangle scoreRec
		{
			static_cast<float>(scoreBound_.windowToScreenPosX),
			static_cast<float>(scoreBound_.windowToScreenPosY),
			static_cast<float>(scoreBound_.windowWidth),
			static_cast<float>(scoreBound_.windowHeight)
		};

		float roundness = 0.2f;
		int frameWidth = 5;
		DrawRectangleRounded(scoreRec, roundness, 1, LIGHTGRAY);
		DrawRectangleRoundedLines(scoreRec, roundness, 1, frameWidth, RED);

		const std::string text = std::to_string(score);
		const int scoreX = scoreBound_.scorePositionX + scoreBound_.windowToScreenPosX;
		const int scoreY = scoreBound_.scorePositionY + scoreBound_.windowToScreenPosY;
		const int fontSize = 100;
		const Color fontColor = WHITE;
		DrawText(text.c_str(), scoreX, scoreY, fontSize, fontColor);
	}

	void drawTile(const Tile& tile, int worldX = 0, int worldY = 0) const
	{
		if (worldY + tile.getY() >= 0)
		{
			Rectangle tileRec
			{
				static_cast<float>(levelBound_.windowToScreenPosX + (worldX + tile.getX()) * levelBound_.tileSize),
				static_cast<float>(levelBound_.windowToScreenPosY + (worldY + tile.getY()) * levelBound_.tileSize),
				static_cast<float>(levelBound_.tileSize),
				static_cast<float>(levelBound_.tileSize)
			};

			float roundness = 0.5f;
			int lineThick = levelBound_.tileSize / 15;
			DrawRectangleRounded(tileRec, roundness, 1, tile.getColor());
			DrawRectangleRoundedLines(tileRec, roundness, 1, lineThick, BLACK);
		}
	}

private:
	const LevelBound levelBound_;
	const ScoreBound scoreBound_;
};