#pragma once

#include <raylib.h>
#include <string_view>
#include "level.h"
#include "tile.h"
#include "figures.h"
#include "soundSystem.h"
#include "observer.h"

// Main player of all players
class Player
{
    using Figure = std::array<Tile, 4>;

public:
    explicit Player(Level* level)
        : level_(level)
    {
        reset();
    }

    void reset() 
    {
        gameOther_ = false;
        player_ = nextFigureRandom();
        nextFigure_ = nextFigureRandom();
        placePlayerToStartPosition();
    }

    // Input
    void updateInput()
    {
        // movement input
        if (IsKeyPressed(KEY_A))  tryToMove("left");
        if (IsKeyPressed(KEY_D))  tryToMove("right");
        if (IsKeyDown(KEY_S))     speed_ = sprintSpeed_;
        if (IsKeyUp(KEY_S))       speed_ = defaultSpeed_;
        if (IsKeyPressed(KEY_W))  tryToRotate();


        // GodMode
        if (IsKeyPressed(KEY_Q)) godMode_ = !godMode_;
        if (godMode_)
        {
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
        
        bool isNotCollideWithWorld = std::all_of(player_.begin(), player_.end(),
                [this, tmpY](const auto& tile)
                {
                    return level_->willNotCollideWith(x_ + tile.getX(),
                                  static_cast<int>(tmpY) + tile.getY());
                });
        
        // check collision with world
        if (isNotCollideWithWorld)
            y_ = tmpY;
        else
        {
            if (detectGameover())
                return;

            firePlayerFellEvent();
            player_ = nextFigure_;
            nextFigure_ = nextFigureRandom();
            placePlayerToStartPosition();
        }
    }

    void updateGraphics(const GraphicsSystem& graphics) const
    {
        // draw player
        graphics.drawPlayer(player_, x_, static_cast<int>(y_));

        // draw nextFigure
        graphics.drawNextFigure(nextFigure_);

        // TODO: draw stash
    }

    bool isInGodMode() const { return godMode_; }
    bool isGameOver() const { return gameOther_;  }
    int getX() const { return x_; }
    int getY() const { return static_cast<int>(y_); }

    Figure getTiles() const { return player_; }
    Subject& fellEvent() { return observers_; }

private:
    bool detectGameover()
    {
        bool isNotCollideWithWorld = std::all_of(player_.begin(), player_.end(),
            [this](const auto& tile)
            {
                return level_->willNotCollideWith(x_ + tile.getX(),
                                                  static_cast<int>(y_) + tile.getY());
            });

        if (!isNotCollideWithWorld)
        {
            gameOther_ = true;
            return true;
        }

        return false;
    }

    void tryToMove(const std::string_view& side)
    {
        int tmpX = 0;
        if (side == "left")  tmpX = x_ - 1;
        if (side == "right") tmpX = x_ + 1;

        // check collision
        if (std::all_of( player_.begin(), player_.end(),
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
        if (std::all_of(player_.begin(), player_.end(),
                [this](const auto& tile)
                {
                    const int tileX = tile.getY();
                    const int tileY = -tile.getX();
                    return level_->willNotCollideWith(x_ + tileX,
                                    static_cast<int>(y_) + tileY);
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

    void firePlayerFellEvent()
    {
        observers_.notify(this, Events::PLAYER_FELL);
        TraceLog(LOG_INFO, "PLAYER_FELL");
    }

    void placePlayerToStartPosition()
    {
        x_ = 4;
        y_ = 1.0f;
    }
    
    [[nodiscard]]
    Figure& nextFigureRandom()
    {
        int random = GetRandomValue(1, 7);

        switch (random)
        {
        case 1: return Figures::o;
        case 2: return Figures::i;
        case 3: return Figures::s;
        case 4: return Figures::z;
        case 5: return Figures::l;
        case 6: return Figures::j;
        case 7: return Figures::t;
        default: return Figures::o;
        }
    }

    float defaultSpeed_ = 1.0f;
    const float sprintSpeed_ = 50.0f;

    int x_ = 0;
    float y_ = 0.0f;
    float speed_ = defaultSpeed_;
    Level* level_;
    Figure player_;
    Figure nextFigure_;
    Subject observers_;

    bool godMode_ = true;
    bool gameOther_ = false;
};