#include "player.h"

using Figure = std::array<Tile, 4>;

Player::Player(Level * level, Score * score)
    : level_(level), score_(score)
{
    reset();
}

void Player::reset()
{
    gameOther_ = false;
    player_ = nextFigureRandom();
    nextFigure_ = nextFigureRandom();
    placePlayerToStartPosition();
    currentSpeed_ = defaultSpeed_;
}

// Input
void Player::updateInput()
{
    // movement input
    if (IsKeyPressed(KEY_A))  tryToMove("left");
    if (IsKeyPressed(KEY_D))  tryToMove("right");
    if (IsKeyDown(KEY_S))     speed_ = sprintSpeed_;
    if (IsKeyUp(KEY_S))       speed_ = currentSpeed_;
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

void Player::updateMovement(const float dt)
{
    float tmpY = y_;
    // increase current speed by the score quantity
    currentSpeed_ = defaultSpeed_ + static_cast<float>(score_->getScore()) * scoreSpeedMult_;

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

void Player::updateGraphics(const GraphicsSystem& graphics) const
{
    // draw player
    graphics.drawPlayer(player_, x_, static_cast<int>(y_));

    // draw nextFigure
    graphics.drawNextFigure(nextFigure_);

    // TODO: draw stash
}

    bool Player::detectGameover()
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

    Figure& Player::nextFigureRandom()
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

    bool Player::tryToMove(const std::string_view& side)
    {
        int tmpX = 0;
        if (side == "left")  tmpX = x_ - 1;
        if (side == "right") tmpX = x_ + 1;

        // check collision
        if (std::all_of(player_.begin(), player_.end(),
        [this, tmpX](const auto& tile)
        {
            return level_->willNotCollideWith(tmpX + tile.getX(),
                                              static_cast<int>(y_) + tile.getY());
        }))
        {
            x_ = tmpX;
            return true;
        }

        return false;
    }

    // Try to rotate player if player will not collide with level
    bool Player::tryToRotate()
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

            return true;
        }

        return false;
    }


    void Player::placePlayerToStartPosition()
    {
        x_ = defaultPosX_;
        y_ = defaultPosY_;
    }


    void Player::firePlayerFellEvent()
    {
        observers_.notify(this, Events::PLAYER_FELL);
        TraceLog(LOG_INFO, "PLAYER_FELL");
    }