#pragma once

#include <raylib.h>
#include <string_view>
#include "level.h"
#include "score.h"
#include "tile.h"
#include "figures.h"
#include "soundSystem.h"
#include "observer.h"

using Figure = std::array<Tile, 4>;

// Main player of all players
class Player
{
public:
    Player(Level* level, Score* score);

    void reset();
    void updateInput();
    void updateMovement(const float dt);
    void updateGraphics(const GraphicsSystem& graphics) const;

    [[nodiscard]] bool isInGodMode() const { return godMode_; }
    [[nodiscard]] bool isGameOver() const { return gameOther_;  }
    [[nodiscard]] int getX() const { return x_; }
    [[nodiscard]] int getY() const { return static_cast<int>(y_); }
    [[nodiscard]] float getSpeed() const { return speed_; }
    [[nodiscard]] Figure getTiles() const { return player_; }
    [[nodiscard]] Subject& fellEvent() { return observers_; }

private:
    [[nodiscard]] bool detectGameover();
    void tryToMove(const std::string_view& side);
    // Try to rotate player if player will not collide with level
    void tryToRotate();
    void placePlayerToStartPosition();
    [[nodiscard]] Figure& nextFigureRandom();
    void firePlayerFellEvent();

    const float defaultSpeed_ = 1.0f;
    const float sprintSpeed_ = 50.0f;
    const float scoreSpeedMult_ = 0.0005f;
    const int defaultPosX = 4;
    const float defaultPosY = 1.0f;
 
    int x_ = 0;
    float y_ = 0.0f;
    float currentSpeed_ = defaultSpeed_;
    float speed_ = currentSpeed_;
    Level* level_;
    Score* score_;
    Figure player_;
    Figure nextFigure_;
    Subject observers_;

    bool godMode_ = true;
    bool gameOther_ = false;
};