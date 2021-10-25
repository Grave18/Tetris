#include <graphicsSystem.h>

GraphicsSystem::GraphicsSystem(const char* title, float width, float height, int fps)
    : title_(title), screenWidth_(width), screenHeight_(height), fps_(fps)
{
    // init
    InitWindow(static_cast<int>(screenWidth_), static_cast<int>(screenHeight_), title_);
    SetTargetFPS(fps_);

    // load resources
    logo_ = LoadTexture("resources/raylib_logo_512.png");
}

GraphicsSystem::~GraphicsSystem()
{
    // destroy
    UnloadTexture(logo_);
    CloseWindow();
}

void GraphicsSystem::resizeWindow(int windowWidth, int windowHeight)
{
    SetWindowSize(windowWidth, windowHeight);
    screenWidth_ = static_cast<float>(windowWidth);
    screenHeight_ = static_cast<float>(windowHeight);
}

void GraphicsSystem::drawTile(const Tile& tile, int worldX, int worldY) const
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

void GraphicsSystem::drawBackground() const
{
    float roundness = 0.07f;
    DrawRectangleRounded(level_, roundness, 1, LIGHTGRAY);
    DrawRectangleRoundedLines(level_, roundness, 1, static_cast<int>(frameWidth_), RED);
}

void GraphicsSystem::drawScore(int score) const
{
    float roundness = 0.2f;
    DrawRectangleRounded(score_, roundness, 1, LIGHTGRAY);
    DrawRectangleRoundedLines(score_, roundness, 1, static_cast<int>(frameWidth_), RED);

    const std::string text = std::to_string(score);
    const auto scoreX = static_cast<int>(score_.x + score_.width / 8);
    const auto scoreY = static_cast<int>(score_.y + score_.height / 5);
    const auto fontSize = static_cast<int>(screenHeight_ / 10);
    const auto fontColor = WHITE;
    DrawText(text.c_str(), scoreX, scoreY, fontSize, fontColor);
}

void GraphicsSystem::drawNextFigure(const Figure& figure) const
{
    for (const auto& tile : figure)
    {
        const auto x = static_cast<int>((nextFigure_.x + nextFigure_.width / 8.0f) / tileSize_);
        const auto y = static_cast<int>((nextFigure_.y + nextFigure_.height / 5.0f) / tileSize_);
        drawTile(tile, x, y);
    }

    float roundness = 0.2f;
    DrawRectangleRounded(nextFigure_, roundness, 1, LIGHTGRAY);
    DrawRectangleRoundedLines(nextFigure_, roundness, 1, static_cast<int>(frameWidth_), RED);
}

void GraphicsSystem::drawLogo() const
{
    DrawTexture(
        logo_,
        static_cast<int>(screenWidth_) / 2 - logo_.width / 2,
        static_cast<int>(screenHeight_) / 2 - logo_.height / 2,
        RAYWHITE);
}