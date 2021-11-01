#pragma once

#include <array>
#include <algorithm>
#include <string>
#include <any>

#include "tile.h"
#include "graphicsSystem.h"
#include "observer.h"

// Game level
class Level : public Observer
{
public:
    void updateGraphics(const GraphicsSystem& graphics) const;
    [[nodiscard]] bool willNotCollideWith(int x, int y) const;
    void clear();

    void onNotify(const std::any& entity, Events event) override;
    [[nodiscard]] Subject& rowClearedEvent() { return observers_; }

private:
    void scanRows();
    void addTile(int x, int y, Color color);
    void clearRow(int row);
    void shiftDownRows(int row);
    void fireRowClearedEvent();

    static const int sLevelWidth_ = 10;
    static const int sLevelHeight_ = 20;
    static const int sMaxSize_ = sLevelWidth_ * sLevelHeight_;
    static const int rowsCount_ = 20;

    // index of neft not occupied tile
    int nextIndex_ = 0;
    // object pool
    std::array<Tile, sMaxSize_> level_;
    // count of filled tiles in all rows of level
    std::array<int, rowsCount_> rows_ = {0};

    Subject observers_;
};