#pragma once

#include <array>
#include <algorithm>
#include <execution>

#include "tile.h"
#include "graphics.h"
#include "levelBounds.h"
#include "observer.h"

// Game level
class Level : public Observer
{
public:
    explicit Level(const LevelBound& bounds)
    :  bounds_(bounds)
    {
        // temporary level fill
        addTile(1, 7, GREEN);
        addTile(9, 5, BLUE);
    }
    Level(Level&) = delete;
    Level(Level&&) = delete;

    void updateGraphics(const Graphics& graphics) const
    {
        graphics.drawLevelBackground();

        // draw level tiles
        for (int i = 0; i < nextIndex_; ++i)
        {
            graphics.drawTile(level_[i]);
        }
    }

    bool willNotCollideWith(int x, int y) const
    {
        // check level bounds
        if (x < 0 || x >= bounds_.width || y >= bounds_.height)
            return false;

        // check each tile for collision
        return std::none_of(level_.begin(), level_.begin() + nextIndex_,
            [x, y](const auto& tile)
            {
                return x == tile.getX() && y == tile.getY();
            });
    }

    void addFigure(const std::array<Tile, 4>& tiles, int x, int y)
    {
        for (const auto& tile : tiles)
        {
            addTile(tile.getX() + x, tile.getY() + y, tile.getColor());
        }
    }

    void addTile(int x, int y, Color color)
    {
        if (nextIndex_ != MAX_SIZE)
        {
            level_[nextIndex_].setTile(x, y, color);
            ++nextIndex_;

            TraceLog(LOG_INFO, ("nextIndex = " + std::to_string(nextIndex_)).c_str());
        }

    }

    void clearRow(int row)
    {
        int  currentIndex = 0;
        while (currentIndex < nextIndex_)
        {
            // check if tile in the row and if true then throw away in the back
            // of active part of array and decrement next index else procced with new index
            if (level_[currentIndex].getY() == row)
            {
                --nextIndex_;
                std::swap(level_[currentIndex], level_[nextIndex_]);
                TraceLog(LOG_INFO, ("nextIndex = " + std::to_string(nextIndex_)).c_str());
            }
            else
                ++currentIndex;
        }

        shiftDownRows(row - 1);
    }

    void shiftDownRows(int row)
    {
        for (int i = 0; i < nextIndex_; ++i) 
            if (level_[i].getY() <= row) 
                level_[i].setY(level_[i].getY() + 1);
    }

    void clear()
    {
        nextIndex_ = 0;
        TraceLog(LOG_INFO, ("nextIndex = " + std::to_string(nextIndex_)).c_str());
    }

    void onNoify(void* entity, Events event) override
    {
        // TODO: delete this or refactor
    }
    
   

private:
    LevelBound bounds_;

    // index of neft not occupied tile
    int nextIndex_ = 0;
    static const size_t MAX_SIZE = 200;
    // object pool
    std::array<Tile, MAX_SIZE> level_;
};