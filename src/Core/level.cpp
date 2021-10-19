#include "level.h"
#include "player.h"
//#include "observer.h"

// public:
void Level::updateGraphics(const GraphicsSystem& graphics) const
{
    graphics.drawLevelBackground();

    // draw level tiles
    for (int i = 0; i < nextIndex_; ++i)
    {
        graphics.drawTile(level_[i]);
    }
}

bool Level::willNotCollideWith(int x, int y) const
{
    // check level bounds
    if (x < 0 || x >= LEVEL_WIDTH || y >= LEVEL_HEIGHT)
        return false;

    // check each tile for collision
    return std::none_of(level_.begin(), level_.begin() + nextIndex_,
                        [x, y](const auto& tile)
    {
        return x == tile.getX() && y == tile.getY();
    });
}

void Level::clear()
{
    nextIndex_ = 0;
    rows_ = { 0 };
    TraceLog(LOG_INFO, ("nextIndex = " + std::to_string(nextIndex_)).c_str());
}

void Level::onNotify(void* entity, Events event)
{
    if (entity && event == Events::PLAYER_FELL)
    {
        auto player = static_cast<Player*>(entity);

        for (const auto& tile : player->getTiles())
        {
            addTile(tile.getX() + player->getX(), tile.getY() + player->getY(), tile.getColor());
        }

        scanRows();
    }
}

// private:
void Level::scanRows()
{
    int i = rowsCount_ - 1;
    while (i >= 0)
    {
        if (rows_[i] == 10)
        {
            clearRow(i);
            TraceLog(LOG_INFO, "ROW_CLEARED_EVENT");
            observers_.notify(this, Events::ROW_CLEARED);
        }
        else --i;
    }
}

void Level::addTile(int x, int y, Color color)
{
    if (nextIndex_ != MAX_SIZE)
    {
        level_[nextIndex_].setTile(x, y, color);
        ++nextIndex_;
        ++rows_[y];

        TraceLog(LOG_INFO, ("nextIndex = " + std::to_string(nextIndex_)).c_str());
        TraceLog(LOG_INFO, ("row " + std::to_string(y) + " = "
                            + std::to_string(rows_[y])).c_str());
    }
}

void Level::clearRow(int row)
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
        else ++currentIndex;
    }

    shiftDownRows(row - 1);
}

void Level::shiftDownRows(int row)
{
    for (int i = 0; i < nextIndex_; ++i)
        if (level_[i].getY() <= row)
        {
            level_[i].setY(level_[i].getY() + 1);
        }

    // refresh number of tiles in rows
    rows_[0] = 0;
    for (int i = row; i >= 0; --i)
    {
        rows_[i + 1] = rows_[i];
        TraceLog(LOG_INFO, ("row " + std::to_string(i + 1) + " = "
                            + std::to_string(rows_[i + 1])).c_str());
    }
}