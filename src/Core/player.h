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

        // movement
        if (IsKeyPressed(KEY_A)) --tmpX;
        if (IsKeyPressed(KEY_D)) ++tmpX;
        if (IsKeyPressed(KEY_W)) --tmpY;
        if (IsKeyPressed(KEY_S)) ++tmpY;

        if (std::all_of(player_.begin(), player_.end(), 
                [this, tmpX, tmpY](const auto& tile)
                {
                    return level_->resolveCollision(tmpX + tile.getX(), tmpY + tile.getY());
                }))
        {
            x_ = tmpX;
            y_ = tmpY;
        }

        // change figure
        if (IsKeyPressed(KEY_O)) player_ = Figures::o;
        if (IsKeyPressed(KEY_I)) player_ = Figures::i;
        if (IsKeyPressed(KEY_X)) player_ = Figures::s;
        if (IsKeyPressed(KEY_Z)) player_ = Figures::z;
        if (IsKeyPressed(KEY_L)) player_ = Figures::l;
        if (IsKeyPressed(KEY_J)) player_ = Figures::j;
        if (IsKeyPressed(KEY_T)) player_ = Figures::t;

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
    std::array<Tile, 4> player_ = Figures::o;
    Level* level_;
};