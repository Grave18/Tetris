#pragma once

#include <raylib.h>
#include <string>
#include "tile.h"

// Provide rendering of a tile
class GraphicsSystem
{
public:
    GraphicsSystem(const char* title, float width, float height, int fps)
        : title_(title), width_(width), height_(height), fps_(fps)
    {
        // init
        InitWindow(static_cast<int>(width_), static_cast<int>(height_), title_);
        SetTargetFPS(fps_);
    }
    GraphicsSystem(GraphicsSystem&) = delete;
    GraphicsSystem(GraphicsSystem&&) = delete;
    GraphicsSystem& operator=(GraphicsSystem&) = delete;
    GraphicsSystem& operator=(GraphicsSystem&&) = delete;
    ~GraphicsSystem()
    {
        // destroy
        CloseWindow();
    }

    void drawTile(const Tile& tile, int worldX = 0, int worldY = 0) const
    {
        if (worldY + tile.getY() >= 0)
        {
            Rectangle tileRec
            {
                level_.x + (worldX + tile.getX()) * tileSize_, // + frameWidth_,
                level_.y + (worldY + tile.getY()) * tileSize_, //+ frameWidth_,
                tileSize_,
                tileSize_
            };

            float roundness = 0.5f;
            auto lineThick = static_cast<int>(tileSize_ / 15);
            DrawRectangleRounded(tileRec, roundness, 1, tile.getColor());
            DrawRectangleRoundedLines(tileRec, roundness, 1, lineThick, BLACK);
        }
    }

    void drawLevelBackground() const
    {
        float roundness = 0.07f;
        DrawRectangleRounded(level_, roundness, 1, LIGHTGRAY);
        DrawRectangleRoundedLines(level_, roundness, 1, static_cast<int>(frameWidth_), RED);
    }

    void drawScore(int score) const
    {
        float roundness = 0.2f;
        DrawRectangleRounded(score_, roundness, 1, LIGHTGRAY);
        DrawRectangleRoundedLines(score_, roundness, 1, static_cast<int>(frameWidth_), RED);

        const std::string text = std::to_string(score);
        const auto scoreX = static_cast<int>(score_.x + score_.width / 8);
        const auto scoreY = static_cast<int>(score_.y + score_.height / 5);
        const auto fontSize = static_cast<int>(height_ / 10);
        const auto fontColor = WHITE;
        DrawText(text.c_str(), scoreX, scoreY, fontSize, fontColor);
    }
    

private:
    const char* title_;
    float width_;
    float height_;
    int fps_;

    float tileSize_ = height_ / 24;    // 1080p -> 45
    float frameWidth_ = height_ / 216; // 1080p -> 5

    // size of level in tiles
    float levelWidth_ = 10.0f;
    float levelHeight_ = 20.0f;
    Rectangle level_
    {
        height_ / 10.0f,          // offset x
        height_ / 10.0f,          // offsetY
        levelWidth_ * tileSize_,  // width
        levelHeight_ * tileSize_  // height
    };

    Rectangle score_
    {
        level_.x + level_.width + height_ / 10.0f, // offset x
        height_ / 10.0f,                           // offsetY
        height_ / 3.6f,                            // width
        height_ / 7.2f                             // height
    };

    Rectangle nextFigure_
    {
        level_.x + level_.width + height_ / 10.0f,  // offset x
        score_.y + score_.height + height_ / 10.0f, // offsetY
        height_ / 3.6f,                             // width
        height_ / 7.2f                              // height
    };

    Rectangle stash_;
};