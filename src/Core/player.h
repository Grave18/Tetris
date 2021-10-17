#pragma once

#include <raylib.h>
#include <string_view>
#include "level.h"
#include "tile.h"
#include "figures.h"
#include "soundSystem.h"
#include "observer.h"

// player's default fall speed
constexpr float DEFAULT_SPEED = 1.0f;
constexpr float SPRINT_SPEED = 8.0f;

// Main player of all players
class Player
{
public:
    explicit Player(Level* level)
        : level_(level)
    {
        placePlayerToStartPosition();
    }
    Player(Player&) = delete;
    Player(Player&&) = delete;

    // Input
    void updateInput()
    {
        // movement input
        if (IsKeyPressed(KEY_A))  tryToMove("left");
        if (IsKeyPressed(KEY_D))  tryToMove("right");
        if (IsKeyPressed(KEY_S))  speed_ = SPRINT_SPEED;
        if (IsKeyReleased(KEY_S)) speed_ = DEFAULT_SPEED;
        if (IsKeyPressed(KEY_W))  tryToRotate();


        // God Mode
        if (IsKeyPressed(KEY_Q)) isInGodMode_ = !isInGodMode_;
        if (isInGodMode_)
        {
            if (IsKeyPressed(KEY_LEFT_SHIFT)) speed_ = SPRINT_SPEED * 3;
            if (IsKeyReleased(KEY_LEFT_SHIFT)) speed_ = DEFAULT_SPEED;
            if (IsKeyPressed(KEY_BACKSPACE)) level_->clear();

            // change figure input
            if (IsKeyPressed(KEY_UP))    --y_;
            if (IsKeyPressed(KEY_DOWN))  ++y_;
            if (IsKeyPressed(KEY_LEFT))  --x_;
            if (IsKeyPressed(KEY_RIGHT)) ++x_;

            if (IsKeyPressed(KEY_O)) player_ = Figures::o;
            if (IsKeyPressed(KEY_I)) player_ = Figures::i;
            if (IsKeyPressed(KEY_X)) player_ = Figures::s;
            if (IsKeyPressed(KEY_Z)) player_ = Figures::z;
            if (IsKeyPressed(KEY_L)) player_ = Figures::l;
            if (IsKeyPressed(KEY_J)) player_ = Figures::j;
            if (IsKeyPressed(KEY_T)) player_ = Figures::t;
        }
    }

    void updateMovement(const float dt)
    {
        float tmpY = y_;

        // falling on ground
        if (dt < 1.0f) 
            tmpY += speed_ * dt;
        else           
            tmpY += 1.0f;

        // check collision
        bool isNotCollide = std::all_of(player_.begin(), player_.end(),
                [this, tmpY](const auto& tile)
                {
                    return level_->willNotCollideWith(x_ + tile.getX(),
                                  static_cast<int>(tmpY) + tile.getY());
                });
        
        if (isNotCollide)
            y_ = tmpY;
        else
        {
            // Fire fell event
            observers_.notify(this, Events::PLAYER_FELL);
            TraceLog(LOG_INFO, "FELL_EVENT");

            placePlayerToStartPosition();
        }
    }

    void updateGraphics(const GraphicsSystem& graphics) const
    {
        for (const auto& tile : player_)
        {
            graphics.drawTile(tile, x_, static_cast<int>(y_));
        }
    }

    bool isInGodMode() const { return isInGodMode_; }
    int getX() const { return x_; }
    int getY() const { return static_cast<int>(y_); }

    std::array<Tile, 4> getTiles() const { return player_; }
    Subject& fellEvent() { return observers_; }

private:
    void tryToMove(const std::string_view& side)
    {
        int tmpX = 0;
        if (side == "left")  tmpX = x_ - 1;
        if (side == "right") tmpX = x_ + 1;

        // check collision
        if (std::all_of(
            player_.begin(),
            player_.end(),
            [this, tmpX](const auto& tile)
        {
            return level_->willNotCollideWith(tmpX + tile.getX(), static_cast<int>(y_) + tile.getY());
        }))
        {
            x_ = tmpX;
        }
    }

    // Try to rotate player if player will not collide with level
    void tryToRotate()
    {
        // rotate if new position of player didn't collide with level
        if (std::all_of(
            player_.begin(),
            player_.end(),
            [this](const auto& tile)
        {
            const int tileX = tile.getY();
            const int tileY = -tile.getX();
            return level_->willNotCollideWith(x_ + tileX, static_cast<int>(y_) + tileY);
        }))
        {
            for (auto& tile : player_)
            {
                const int x = tile.getY();
                const int y = -tile.getX();
                tile.setX(x);
                tile.setY(y);
            }
        }
    }

    void placePlayerToStartPosition()
    {
        x_ = 5;
        y_ = 3.0f;
    }

    int x_ = 0;
    float y_ = 0.0f;
    float speed_ = DEFAULT_SPEED;
    bool isInGodMode_ = true;
    std::array<Tile, 4> player_ = Figures::j;
    Level* level_;

    Subject observers_;
};