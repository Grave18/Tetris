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

    // Input
    void updateInput()
    {
        tmpX_ = x_;
        tmpY_ = y_;

        // movement
        if (IsKeyPressed(KEY_A)) --tmpX_;
        if (IsKeyPressed(KEY_D)) ++tmpX_;
        if (IsKeyPressed(KEY_W)) --tmpY_;
        if (IsKeyPressed(KEY_S)) ++tmpY_;
        

        if (IsKeyPressed(KEY_Q)) isGodMode_ = !isGodMode_;
        // change figure
        if (isGodMode_)
        {
            if (IsKeyPressed(KEY_O)) player_ = Figures::o;
            if (IsKeyPressed(KEY_I)) player_ = Figures::i;
            if (IsKeyPressed(KEY_X)) player_ = Figures::s;
            if (IsKeyPressed(KEY_Z)) player_ = Figures::z;
            if (IsKeyPressed(KEY_L)) player_ = Figures::l;
            if (IsKeyPressed(KEY_J)) player_ = Figures::j;
            if (IsKeyPressed(KEY_T)) player_ = Figures::t;
        }
    }

    // Movement
    void updateMovement(const float dt)
    {
        if (std::all_of(
                player_.begin(), 
                player_.end(),
                [=](const auto& tile)
                {
                    return level_->resolveCollision(static_cast<int>(tmpX_) + tile.getX(),
                                                    static_cast<int>(tmpY_) + tile.getY());
                }))
        {
            x_ = tmpX_;
            y_ = tmpY_;
        }

        if (dt < 1.0f) y_ += speed_ * dt;
        else           y_ += 1.0f;
    }

    // Graphics
    void updateGraphics(const Graphics& graphics) const
    {
        for (const auto& tile : player_)
        {
            graphics.drawTile(tile, static_cast<int>(x_), static_cast<int>(y_));
        }
    }

    bool isGodMode() const { return isGodMode_; }
    float getX() const { return x_; }
    float getY() const { return y_; }

private:
    float x_ = 5.0f;
    float y_ = 3.0f;
    float tmpX_ = 0.0f;
    float tmpY_ = 0.0f;
    float speed_ = 1.0f;
    bool isGodMode_ = true;
    std::array<Tile, 4> player_ = Figures::o;
    Level* level_;
};