#pragma once

#include <raylib.h>
#include "level.h"
#include "tile.h"

class Player
{
public:
    Player(Level* level)
        : level_(level)
        , player_(0, 0, RED)
    {}
    Player(Player&) = delete;
    Player(Player&&) = delete;

    void updateInput()
    {
        if (IsKeyPressed(KEY_A))
        {
            --x_;
        }

        if (IsKeyPressed(KEY_D))
        {
            ++x_;
        }

        if (IsKeyPressed(KEY_W))
        {
            --y_;
        }

        if (IsKeyPressed(KEY_S))
        {
            ++y_;
        }
    }

    void updateGraphics(Graphics& graphics)
    {
        graphics.drawTile(player_, x_, y_);
    }

private:
    int x_ = 0, y_ = 0;
    Tile player_;
    Level* level_;
};