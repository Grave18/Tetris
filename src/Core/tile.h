#pragma once

#include <raylib.h>

// Minimal part of the level
class Tile
{
public:
    Tile(int x = 0, int y = 0, Color color = BLACK)
        : x_(x), y_(y),  color_(color)
    {}

    void setX(int x) { x_ = x; }
    void setY(int y) { y_ = y; }
    int getX() const { return x_; }
    int getY() const { return y_; }
    Color getColor() const { return color_; }
    void setColor(Color color) { color_ = color; }
    void setTile(int x, int y, Color color)
    {
        x_ = x;
        y_ = y;
        color_ = color;
    }

private:
    int x_;
    int y_;
    Color color_;
};
