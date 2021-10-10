#pragma once

#include <vector>

#include "tile.h"
#include "graphics.h"
#include "levelBounds.h"

// Game level
class Level
{
public:
    Level(const LevelBounds& bounds)
    :  bounds_(bounds), level_(bounds.width * bounds.height)
    {
        // temporary level fill
        Tile tile1 = Tile(1,  1, GREEN, true);
        Tile tile2 = Tile(10, 5, BLUE,  true);
        level_.push_back(tile1);
        level_.push_back(tile2);
    }
    Level(Level&) = delete;
    Level(Level&&) = delete;

    void updateGraphics(Graphics& graphics)
    {
        graphics.drawLevelFrame();

        // draw level tiles
        for (const auto& tile : level_)
        {
            if(tile.isOccupied) 
                graphics.drawTile(tile);
        }
    }

    bool resolveCollision(int x, int y)
    {
        // check level bounds
        if (x < 0 || y < 0 || x >= bounds_.width || y >= bounds_.height)
            return false;

        // check each tile for collision
        for(const auto& tile : level_)
        {
            if (tile.isOccupied && x == tile.getX() && y == tile.getY())
                return false;
        }

        return true;
    }

private:
    LevelBounds bounds_;
    std::vector<Tile> level_;
};