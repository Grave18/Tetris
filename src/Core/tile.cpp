#include "tile.h"

Tile::Tile(int x = 0, int y = 0, Color color = BLACK)
    : x_(x), y_(y), color_(color)
{ }

void Tile::setTile(int x, int y, Color color)
{
    x_ = x;
    y_ = y;
    color_ = color;
}