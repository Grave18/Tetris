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
    Level() = default;

    void clear();
    void updateGraphics(const GraphicsSystem& graphics) const;
    [[nodiscard]] bool willNotCollideWith(int x, int y) const;

    // notify all observers of row cleared event
    void onNotify(const std::any& entity, Events event) override;
    [[nodiscard]] Subject& rowClearedEvent() { return observers_; }

private:
    void scanRows();
    void addTile(int x, int y, Color color);
    void clearRow(int row);
    void shiftDownRows(int row);

    void fireRowClearedEvent();

    // index of neft not occupied tile
    int nextIndex_ = 0;
    static const int sLevelWidth_ = 10;
    static const int sLevelHeight_ = 20;
    static const int sMaxSize_ = sLevelWidth_ * sLevelHeight_;
    // object pool
    std::array<Tile, sMaxSize_> level_;

    static const int rowsCount_ = 20;
    std::array<int, rowsCount_> rows_ = {0};

    Subject observers_;
};