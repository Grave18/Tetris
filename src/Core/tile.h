#pragma once

#include <raylib.h>

// Minimal part of the level
class Tile
{
public:
    bool isOccupied;

    Tile(int x = 0, int y = 0, Color color = BLACK, bool isOccupied = false )
        : x_(x), y_(y),  color_(color), isOccupied(isOccupied)
    {}

    void setX(int x) { x_ = x; }
    void setY(int y) { y_ = y; }
    int getX() const { return x_; }
    int getY() const { return y_; }
    Color getColor() const { return color_; }

private:
    int x_, y_;
    Color color_;
};
