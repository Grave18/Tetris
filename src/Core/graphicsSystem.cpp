#include <graphicsSystem.h>

using Figure = std::array<Tile, 4>;

GraphicsSystem::GraphicsSystem(const char* title,
                               int windowWidth,
                               int windowHeight,
                               int fps)
    : screenWidth_ (static_cast<float>(windowWidth ))
    , screenHeight_(static_cast<float>(windowHeight))
{
    // init
    InitWindow(static_cast<int>(screenWidth_),
               static_cast<int>(screenHeight_),
               title);
    SetTargetFPS(fps);

    resetStructs();

    // load resources
    logo_ = LoadTexture("resources/raylib_logo_512.png");
}

GraphicsSystem::~GraphicsSystem()
{
    // destroy
    UnloadTexture(logo_);
    CloseWindow();
}

void GraphicsSystem::resize(int windowWidth, int windowHeight)
{
    SetWindowSize(windowWidth, windowHeight);
    screenWidth_ = static_cast<float>(windowWidth);
    screenHeight_ = static_cast<float>(windowHeight);
    
    resetStructs();
}


void GraphicsSystem::drawLogo() const
{
    DrawTexture(
        logo_,
        static_cast<int>(screenWidth_) / 2 - logo_.width / 2,
        static_cast<int>(screenHeight_) / 2 - logo_.height / 2,
        RAYWHITE);
}

void GraphicsSystem::drawBackground() const
{
    //TODO: raplace with texture or something
    // level back
    float roundness = 0.07f;
    DrawRectangleRounded(level_, roundness, 1, LIGHTGRAY);
    DrawRectangleRoundedLines(level_, roundness, 1, static_cast<int>(frameWidth_), RED);

    // score back
    roundness = 0.2f;
    DrawRectangleRounded(score_, roundness, 1, LIGHTGRAY);
    DrawRectangleRoundedLines(score_, roundness, 1, static_cast<int>(frameWidth_), RED);

    // next back
    roundness = 0.2f;
    DrawRectangleRounded(nextFigure_, roundness, 1, LIGHTGRAY);
    DrawRectangleRoundedLines(nextFigure_, roundness, 1, static_cast<int>(frameWidth_), RED);
}

void GraphicsSystem::drawLevel(const std::array<Tile, 200>& level, int count) const
{
    for (int i = 0; i < count; ++i)
    {
        drawTile(level[i]);
    }
}

void GraphicsSystem::drawPlayer(const Figure& player, int worldX, int worldY) const
{
    for (const auto& tile : player)
    {
        drawTile(tile, worldX, worldY);
    }
}

void GraphicsSystem::drawNextFigure(const Figure& figure) const
{
    for (const auto& tile : figure)
    {
        const auto x = static_cast<int>((nextFigure_.x + nextFigure_.width / 8.0f) / tileSize_);
        const auto y = static_cast<int>((nextFigure_.y + nextFigure_.height / 5.0f) / tileSize_);
        drawTile(tile, x, y);
    }
}


void GraphicsSystem::drawScore(int score) const
{
    const std::string text = std::to_string(score);
    const auto scoreX = static_cast<int>(score_.x + score_.width / 8);
    const auto scoreY = static_cast<int>(score_.y + score_.height / 5);
    const auto fontSize = static_cast<int>(screenHeight_ / 10);
    const auto fontColor = WHITE;
    DrawText(text.c_str(), scoreX, scoreY, fontSize, fontColor);
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

void GraphicsSystem::resetStructs()
{
    tileSize_ = screenHeight_ / 24;    // 1080p -> 45
    frameWidth_ = screenHeight_ / 216; // 1080p -> 5
   
    level_.x      = screenHeight_ / 10.0f;    // offset x
    level_.y      = screenHeight_ / 10.0f;    // offsetY
    level_.width  = levelWidth_ * tileSize_;  // width
    level_.height = levelHeight_ * tileSize_; // height
    
    score_.x      = level_.x + level_.width + screenHeight_ / 10.0f; // offset x
    score_.y      = screenHeight_ / 10.0f;                           // offsetY
    score_.width  = screenHeight_ / 3.6f;                            // width
    score_.height = screenHeight_ / 7.2f;                            // height
    
    nextFigure_.x      = level_.x + level_.width + screenHeight_ / 10.0f;  // offset x
    nextFigure_.y      = score_.y + score_.height + screenHeight_ / 10.0f; // offsetY
    nextFigure_.width  = screenHeight_ / 3.6f;                             // width
    nextFigure_.height = screenHeight_ / 7.2f;                             // height

}