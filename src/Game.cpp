/*
* This game is classic tetris, with figures with 4 components
* Coded with use of RayLib 3.7
* Tile - minimal component of figure and level
*
* Эта игра классический тетрис, где фигура состоит из 4ч компонентов
* написана с помощью RayLib 3.7
* Tile - минимальная единица, из чего состоит фигура и уровень
*/

#include <string>
#include <vector>
#include <raylib.h>

#ifdef _DEBUG
#include <iostream>
#endif

#include "player.h"
#include "level.h"
#include "graphics.h"
#include "levelBounds.h"
#include "soundSystem.h"

int main()
{
    constexpr int windowWidth = 1920;
    constexpr int windowHeight = 1080;
    const char* title = "Tetris";

    // compile time select the size of tile by the size of the screen
    constexpr int tileSize = windowHeight / 24;
    constexpr int levelWidth = 10;
    constexpr int levelHeight = 20;
    constexpr int levelOffsetX = 100;
    constexpr int levelOffsetY = 100;

    InitWindow(windowWidth, windowHeight, title);
    SetTargetFPS(60);

    LevelBound levelBound{levelOffsetX, levelOffsetY, levelWidth, levelHeight, tileSize};
    GraphicsSystem graphics(levelBound);
    SoundSystem sound;
    Level level(levelBound);
    Player player(&level);

    // add events
    player.getObservers().addObserver(&sound);
    level.getObservers().addObserver(&sound);

    while (!WindowShouldClose())
    {
        player.updateInput();
        player.updateMovement(GetFrameTime());

        BeginDrawing();
            ClearBackground(RAYWHITE);

            level. updateGraphics(graphics);
            player.updateGraphics(graphics);
            if (player.isInGodMode()) DrawFPS(10, 10);
            

        EndDrawing();
    }

    CloseWindow();
}
