#pragma once

#include <array>
#include <algorithm>
#include <string>

#include "tile.h"
#include "graphics.h"
#include "observer.h"

// Game level
class Level : public Observer
{
public:
    explicit Level() = default;
    Level(Level&) = delete;
    Level(Level&&) = delete;

    void updateGraphics(const GraphicsSystem& graphics) const;
    bool willNotCollideWith(int x, int y) const;
    void clear();

    void onNotify(void* entity, Events event) override;
    Subject& clearedRowEvent() { return observers_; }

private:
    void scanRows();
    void addTile(int x, int y, Color color);
    void clearRow(int row);
    void shiftDownRows(int row);

    // index of neft not occupied tile
    int nextIndex_ = 0;
    static const int LEVEL_WIDTH = 10;
    static const int LEVEL_HEIGHT = 20;
    static const int MAX_SIZE = LEVEL_WIDTH * LEVEL_HEIGHT;
    // object pool
    std::array<Tile, MAX_SIZE> level_;

    static const int rowsCount_ = 20;
    std::array<int, rowsCount_> rows_ {0};

    Subject observers_;
};