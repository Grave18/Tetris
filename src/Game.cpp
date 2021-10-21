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

//#define RAYGUI_IMPLEMENTATION
//#include <shapes/raygui.h>

#ifdef _DEBUG
#include <iostream>
#endif

#include "graphicsSystem.h"
#include "soundSystem.h"
#include "menuSystem.h"
#include "player.h"
#include "level.h"
#include "score.h"

enum class GameScreens
{
    INTRO = 0, MENU, OPTIONS, GAMEPLAY, GAMEOVER 
};

int main()
{
    const char* title = "Tetris";
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;
    constexpr int fps = 60;

    GraphicsSystem graphics(title, screenWidth, screenHeight, fps);
    SoundSystem sound;
    MenuSystem menu(screenWidth, screenHeight);

    Level level;
    Player player(&level);
    Score score;

    GameScreens currentScreen = GameScreens::INTRO;

    // add events
    player.fellEvent().addObserver(&level);
    player.fellEvent().addObserver(&sound);
    player.fellEvent().addObserver(&score);
    level.clearedRowEvent().addObserver(&sound);
    level.clearedRowEvent().addObserver(&score);

    float timeToMenuScreen = 0.0f;
    SetMousePosition(0, 0);
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        Vector2 mousePos = GetMousePosition();
        bool isLeftMouseButtonPressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            switch (currentScreen)
            {
            case GameScreens::INTRO:
            {
                timeToMenuScreen += dt;
                if (timeToMenuScreen > 3.0f)
                {
                    currentScreen = GameScreens::MENU;
                    timeToMenuScreen = 0.0f;
                }
                graphics.drawLogo();
                break;
            }
            case GameScreens::MENU:
            {
                // menu text
                menu.text("Menu", 0.1f, 0.5f, 0.1f);

                // play button
                Rectangle playButtonBounds;
                menu.button("Play", 0.05f, 0.5f, 0.3f, playButtonBounds, mousePos);

                if (menu.isButtonPressed(playButtonBounds, mousePos, isLeftMouseButtonPressed))
                {
                    player.reset();
                    currentScreen = GameScreens::GAMEPLAY;
                }

                // options button
                Rectangle optionsButtonBounds;
                menu.button("Options", 0.05f, 0.5f, 0.4f, optionsButtonBounds, mousePos);

                if (menu.isButtonPressed(optionsButtonBounds, mousePos, isLeftMouseButtonPressed))
                {
                    currentScreen = GameScreens::OPTIONS;
                }
                
                break;
            }

            case GameScreens::OPTIONS:
            {
                menu.text("Volume:", 0.05f, 0.15f, 0.1f);
                float soundVolume = menu.scrollBar(0.45f, 0.1f, 0.3f, 0.06f, mousePos, isLeftMouseButtonPressed, 0.5f);
                sound.setSoundVolume(soundVolume);

                Rectangle backButtonBounds;
                menu.button("Back", 0.05f, 0.15f, 0.2f, backButtonBounds, mousePos);

                if (menu.isButtonPressed(backButtonBounds, mousePos, isLeftMouseButtonPressed))
                {
                    currentScreen = GameScreens::MENU;
                }
                
                break;
            }

            case GameScreens::GAMEPLAY:
            {
                player.updateInput();
                player.updateMovement(dt);
                if (player.isGameOver())
                    currentScreen = GameScreens::GAMEOVER;

                level.updateGraphics(graphics);
                player.updateGraphics(graphics);
                score.updateGraphics(graphics);
                if (player.isInGodMode())
                    DrawFPS(10, 10);
                break;
            }
            case GameScreens::GAMEOVER:
            {
                timeToMenuScreen += dt;
                if (timeToMenuScreen > 3.0f)
                    currentScreen = GameScreens::MENU;

                const char* text = "GameOver";
                const int fontSize = 200;
                const int textWidth = MeasureText(text, fontSize);
                DrawText(text, screenWidth / 2 - textWidth / 2, screenHeight / 5, fontSize, BLACK);
                break;
            }
            default:
                TraceLog(LOG_WARNING, "SCREEN_IS_NOT_DEFINED.");
            }

        EndDrawing();
    }
}
