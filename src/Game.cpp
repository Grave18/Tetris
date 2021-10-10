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

#include "Core/player.h"
#include "Core/level.h"
#include "Core/graphics.h"

constexpr int levelWidth = 10;
constexpr int levelHeight = 20;
constexpr int sectorSize = 50;
constexpr int windowWidth = 1920;
constexpr int windowHeight = 1080;
const char* title = "Tetris";

int main()
{
	InitWindow(windowWidth, windowHeight, title);
	SetTargetFPS(60);

	Graphics graphics(sectorSize);
	Level level(levelWidth, levelHeight);
	Player player(&level);

	while (!WindowShouldClose())
	{
		player.updateInput();

		BeginDrawing();
			ClearBackground(RAYWHITE);

			player.updateGraphics(graphics);
			//level. updateGraphics(graphics);

		EndDrawing();
	}

	CloseWindow();
}
