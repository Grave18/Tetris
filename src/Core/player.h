#pragma once

#include <raylib.h>
#include "level.h"
#include "tile.h"

// Main player of all players
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
        int tmpX = x_;
        int tmpY = y_;

        if (IsKeyPressed(KEY_A)) --tmpX;
        if (IsKeyPressed(KEY_D)) ++tmpX;
        if (IsKeyPressed(KEY_W)) --tmpY;
        if (IsKeyPressed(KEY_S)) ++tmpY;

        if (level_->resolveCollision(tmpX, tmpY))
        {
            x_ = tmpX;
            y_ = tmpY;
        }
    }

    void updateGraphics(Graphics& graphics)
    {
        player_.setX(x_);
        player_.setY(y_);
        graphics.drawTile(player_);
    }

private:
    int x_ = 0, y_ = 0;
    Tile player_;
    Level* level_;
};