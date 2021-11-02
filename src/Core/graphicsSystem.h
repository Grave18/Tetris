#pragma once

#include <raylib.h>
#include <string>
#include <array>
#include "tile.h"

// Provide rendering of a tile
class GraphicsSystem
{
    using Figure = std::array<Tile, 4>;

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
    void resetStructs();

    // size of main window
    float screenWidth_;
    float screenHeight_;
    // size of level in tiles
    float levelWidth_ = 10.0f;
    float levelHeight_ = 20.0f;
    // size of tile relative to window size
    float tileSize_;
    // size of frame relative to window size
    float frameWidth_;
    
    // logo texture
    Texture2D logo_;

    // background rectangles:
    Rectangle level_;
    Rectangle score_;
    Rectangle nextFigure_;
    //TODO: Rectangle stash_;
};