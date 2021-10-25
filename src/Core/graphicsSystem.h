#pragma once

#include <raylib.h>
#include <string>
#include <array>
#include "tile.h"

enum class FigureType
{
    PLAYER = 0, NEXT, STASH
};

// Provide rendering of a tile
class GraphicsSystem
{
    using Figure = std::array<Tile, 4>;

public:
    GraphicsSystem(const char* title, float width, float height, int fps);
    ~GraphicsSystem();
    void resizeWindow(int windowWidth, int windowHeight);
    void drawTile(const Tile& tile, int worldX = 0, int worldY = 0) const;
    void drawBackground() const;
    void drawScore(int score) const;
    void drawNextFigure(const Figure& figure) const;
    void drawLogo() const;

private:
    const char* title_;
    float screenWidth_;
    float screenHeight_;
    int fps_;

    float tileSize_ = screenHeight_ / 24;    // 1080p -> 45
    float frameWidth_ = screenHeight_ / 216; // 1080p -> 5

    // size of level in tiles
    float levelWidth_ = 10.0f;
    float levelHeight_ = 20.0f;

    Texture2D logo_;

    Rectangle level_
    {
        screenHeight_ / 10.0f,    // offset x
        screenHeight_ / 10.0f,    // offsetY
        levelWidth_ * tileSize_,  // width
        levelHeight_ * tileSize_  // height
    };

    Rectangle score_
    {
        level_.x + level_.width + screenHeight_ / 10.0f, // offset x
        screenHeight_ / 10.0f,                           // offsetY
        screenHeight_ / 3.6f,                            // width
        screenHeight_ / 7.2f                             // height
    };

    Rectangle nextFigure_
    {
        level_.x + level_.width + screenHeight_ / 10.0f,  // offset x
        score_.y + score_.height + screenHeight_ / 10.0f, // offsetY
        screenHeight_ / 3.6f,                             // width
        screenHeight_ / 7.2f                              // height
    };

    //Rectangle stash_;
};