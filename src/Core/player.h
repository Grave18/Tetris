#pragma once

#include <raylib.h>
#include "level.h"
#include "tile.h"
#include "figures.h"

// Main player of all players
class Player
{
public:
    explicit Player(Level* level)
        : level_(level) 
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

        const auto isNotCollided = [this, tmpX, tmpY](const auto& tile)
        {
            return level_->resolveCollision(tmpX + tile.getX(), tmpY + tile.getY());
        };

        if (std::all_of(player_.begin(), player_.end(), isNotCollided))
        {
            x_ = tmpX;
            y_ = tmpY;
        }
    }

    void updateGraphics(Graphics& graphics) const
    {
        for (const auto& tile : player_)
        {
            graphics.drawTile(tile, x_, y_);
        }
    }

private:
    int x_ = 5;
    int y_ = 3;
    std::array<Tile, 4> player_ = Figures::i;
    Level* level_;
};