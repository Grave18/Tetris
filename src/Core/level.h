#pragma once

#include <vector>
#include <algorithm>
#include <execution>

#include "tile.h"
#include "graphics.h"
#include "levelBounds.h"

// Game level
class Level
{
public:
    explicit Level(const LevelBound& bounds)
    :  bounds_(bounds), level_(bounds.width * bounds.height)
    {
        // temporary level fill
        auto tile1 = Tile(1,  7, GREEN, true);
        auto tile2 = Tile(9, 5, BLUE,  true);
        level_.push_back(tile1);
        level_.push_back(tile2);
    }
    Level(Level&) = delete;
    Level(Level&&) = delete;

    void updateGraphics(const Graphics& graphics) const
    {
        graphics.drawLevelBackground();

        // draw level tiles
        for (const auto& tile : level_)
        {
            if(tile.isOccupied()) 
                graphics.drawTile(tile);
        }
    }

    bool willNotCollideWith(int x, int y) const
    {
        // check level bounds
        if (x < 0 || x >= bounds_.width || y >= bounds_.height)
            return false;

        // check each tile for collision
        return std::none_of(level_.begin(), level_.end(),
            [x, y](const auto& tile)
            {
                return tile.isOccupied() && x == tile.getX() && y == tile.getY();
            });
    }

private:
    LevelBound bounds_;
    std::vector<Tile> level_;
};