#pragma once

#include <vector>

#include "tile.h"
#include "graphics.h"

// Представляет собой игровой мир
class Level
{
public:
	Level(int width, int height)
	: width_(width), height_(height), level_(width_ * height_)
	{}
	Level(Level&) = delete;
	Level(Level&&) = delete;

	void updateGraphics(Graphics& graphics)
	{
		//graphics.drawTile()
	}

	void resolveCollision(int x, int y)
	{

	}

private:
	int width_;
	int height_;
	std::vector<Rectangle> level_;
};