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
    constexpr int windowWidth = 800;
    constexpr int windowHeight = 600;
    constexpr int fps = 60;

    GraphicsSystem graphics(title, windowWidth, windowHeight, fps);
    SoundSystem sound;
    MenuSystem menu(windowWidth, windowHeight);

    Level level;
    Score score;
    Player player(&level, &score);

    GameScreens currentScreen = GameScreens::GAMEPLAY;

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

            // Interface state machine
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
                bool isPressed =
                    menu.button("Play", 0.05f, 0.5f, 0.3f, mousePos, isLeftMouseButtonPressed);
                if (isPressed)
                    currentScreen = GameScreens::GAMEPLAY;

                // options button
                isPressed = 
                    menu.button("Options", 0.05f, 0.5f, 0.4f, mousePos, isLeftMouseButtonPressed);
                if (isPressed)
                    currentScreen = GameScreens::OPTIONS;
                
                break;
            }

            case GameScreens::OPTIONS:
            {
                // sound volume bar
                menu.text("Volume:", 0.05f, 0.15f, 0.1f);
                float soundVolume =
                    menu.scrollBar(0.45f, 0.1f, 0.3f, 0.06f, mousePos, isLeftMouseButtonPressed, 0.5f);
                sound.setSoundVolume(soundVolume);
                //DrawText(std::to_string(soundVolume).c_str(), 20, 20, 20, BLACK);

                // back button
                bool isPressed = 
                    menu.button("Back", 0.05f, 0.15f, 0.2f, mousePos, isLeftMouseButtonPressed);
                if (isPressed)
                    currentScreen = GameScreens::MENU;
                
                // resolution buttons
                menu.text("Resolution:", 0.05f, 0.20f, 0.3f);

                isPressed = menu.button("480p", 0.05f, 0.15f, 0.4f, mousePos, isLeftMouseButtonPressed);
                if (isPressed)
                {
                    //TODO: fix this kostyl
                    isLeftMouseButtonPressed = false;
                    int newWidth = 640;
                    int newHeight = 480;
                    graphics.resize(newWidth, newHeight);
                    menu.resize(newWidth, newHeight);
                }
                isPressed = menu.button("600p", 0.05f, 0.15f, 0.5f, mousePos, isLeftMouseButtonPressed);
                if (isPressed)
                {
                    //TODO: fix this kostyl
                    isLeftMouseButtonPressed = false;
                    int newWidth = 800;
                    int newHeight = 600;
                    graphics.resize(newWidth, newHeight);
                    menu.resize(newWidth, newHeight);
                }
                isPressed = menu.button("1080p", 0.05f, 0.15f, 0.6f, mousePos, isLeftMouseButtonPressed);
                if (isPressed)
                {
                    int newWidth = 1920;
                    int newHeight = 1080;
                    graphics.resize(newWidth, newHeight);
                    menu.resize(newWidth, newHeight);
                }

                break;
            }

            case GameScreens::GAMEPLAY:
            {
                // logic
                if (player.isGameOver())
                {
                    // reset level
                    score.clear();
                    level.clear();
                    player.reset();
                    currentScreen = GameScreens::GAMEOVER;
                }
                player.updateInput();
                player.updateMovement(dt);

                // darawing
                graphics.drawBackground();
                level.updateGraphics(graphics);
                player.updateGraphics(graphics);
                score.updateGraphics(graphics);
                if (player.isInGodMode())
                {
                    DrawFPS(10, 10);
                    DrawText(std::to_string(player.getSpeed()).c_str(), 10, 30, 20, BLACK);
                }
                break;
            }
            case GameScreens::GAMEOVER:
            {
                // logic
                timeToMenuScreen += dt;
                if (timeToMenuScreen > 3.0f)
                {
                    currentScreen = GameScreens::MENU;
                    timeToMenuScreen = 0.0f;
                }

                // drawing
                menu.text("GameOver", 0.1f, 0.5f, 0.5f);

                break;
            }
            default:
                TraceLog(LOG_WARNING, "SCREEN_IS_NOT_DEFINED.");
            }

        EndDrawing();
    }
}
