#pragma once

#include <raylib.h>

// Minimal part of the level
class Tile
{
public:
    Tile(int x, int y, Color color);

    [[nodiscard]] int getX() const { return x_; }
    [[nodiscard]] int getY() const { return y_; }
    [[nodiscard]] Color getColor() const { return color_; }
    void setX(int x) { x_ = x; }
    void setY(int y) { y_ = y; }
    void setColor(Color color) { color_ = color; }
    void setTile(int x, int y, Color color);

private:
    int x_;
    int y_;
    Color color_;
};
