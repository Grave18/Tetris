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
#include "soundSystem.h"
#include "score.h"

int main()
{
    const char* title = "Tetris";
    constexpr float windowWidth = 1920;
    constexpr float windowHeight = 1080;
    constexpr int fps = 60;

    GraphicsSystem graphics(title, windowWidth, windowHeight, fps);
    SoundSystem sound;

    Level level;
    Player player(&level);
    Score score;

    // add events
    player.fellEvent().addObserver(&level);
    player.fellEvent().addObserver(&sound);
    player.fellEvent().addObserver(&score);
    level.clearedRowEvent().addObserver(&sound);
    level.clearedRowEvent().addObserver(&score);

    while (!WindowShouldClose())
    {
        player.updateInput();
        player.updateMovement(GetFrameTime());

        BeginDrawing();
            ClearBackground(RAYWHITE);

            level. updateGraphics(graphics);
            player.updateGraphics(graphics);
            score.updateGraphics(graphics);
            if (player.isInGodMode()) DrawFPS(10, 10);
            

        EndDrawing();
    }
}
