#pragma once

#include <raylib.h>

// Minimal part of the level
class Tile
{
public:
    Tile(int x = 0, int y = 0, Color color = BLACK, bool isOccupied = false )
        : x_(x), y_(y),  color_(color), isOccupied_(isOccupied)
    {}

    void setX(int x) { x_ = x; }
    void setY(int y) { y_ = y; }
    int getX() const { return x_; }
    int getY() const { return y_; }
    bool isOccupied() const  { return isOccupied_; }
    void setOccupied(bool flag) { isOccupied_ = flag;  }
    Color getColor() const { return color_; }

private:
    int x_;
    int y_;
    Color color_;
    bool isOccupied_;
};
