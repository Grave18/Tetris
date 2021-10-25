#pragma once

#include <raylib.h>
#include <string>
#include <array>
#include "tile.h"

    using Figure = std::array<Tile, 4>;
// Provide rendering of a tile
class GraphicsSystem
{

public:
    GraphicsSystem(const char* title, int windowWidth, int windowHeight, int fps);
    ~GraphicsSystem();
    void resize(int windowWidth, int windowHeight);

    // drawing API functions:
    void drawLogo() const;
    void drawBackground() const;
    void drawLevel(const std::array<Tile, 200>& level, int nextIndex) const;
    void drawPlayer(const Figure& figure, int worldX, int worldY) const;
    void drawNextFigure(const Figure& figure) const;
    void drawStash(const Figure& figure) const;
    void drawScore(int score) const;

private:
    void drawTile(const Tile& tile, int worldX = 0, int worldY = 0) const;

    // size of main window
    float screenWidth_;
    float screenHeight_;
    // size of level in tiles
    float levelWidth_ = 10.0f;
    float levelHeight_ = 20.0f;
    // size of tile relative to window size
    float tileSize_ = screenHeight_ / 24;    // 1080p -> 45
    // size of frame relative to window size
    float frameWidth_ = screenHeight_ / 216; // 1080p -> 5
    
    // logo texture
    Texture2D logo_;

    // background rectangles:
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