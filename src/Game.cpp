/*
*Эта игра классический тетрис, написана с помощью RayLib 3
*Rec(значит rectangle) - минимальная единица, из чего состоит фигура и уровень
*/ 

#include "Game.h"

const int level_width = 10;
const int level_height = 20;
const int sector_size = 50;
const int scr_width = level_width * sector_size;
const int scr_height = level_height * sector_size;
const char* title = "Tetris";

int main()
{
	InitWindow(scr_width, scr_height, title);
	SetTargetFPS(60);

	
	int bound_x = scr_width / sector_size;
	int bound_y = scr_height / sector_size;

	World world = World(bound_x, bound_y);
	Player player = Player(&world, FigureEnum::I);

	while (!WindowShouldClose())
	{
		using namespace std::string_literals; // для ""s

		// Управление
		if (IsKeyPressed(KEY_UP) && player.CanMove("up"))
			player.y -= 1;
		if (IsKeyDown(KEY_DOWN) && player.CanMove("down") )
			player.y += 1;
		if (IsKeyPressed(KEY_RIGHT) && player.CanMove("right") )
			player.x += 1;
		if (IsKeyPressed(KEY_LEFT) && player.CanMove("left"))
			player.x -= 1;

		if (IsKeyPressed(KEY_O))
			player.ChangeFigure(FigureEnum::O);
		if (IsKeyPressed(KEY_I))
			player.ChangeFigure(FigureEnum::I);
		if (IsKeyPressed(KEY_S))
			player.ChangeFigure(FigureEnum::S);
		if (IsKeyPressed(KEY_Z))
			player.ChangeFigure(FigureEnum::Z);
		if (IsKeyPressed(KEY_L))
			player.ChangeFigure(FigureEnum::L);
		if (IsKeyPressed(KEY_J))
			player.ChangeFigure(FigureEnum::J);
		if (IsKeyPressed(KEY_T))
			player.ChangeFigure(FigureEnum::T);

		BeginDrawing();

			ClearBackground(RAYWHITE);

			for (int i = 0; i < player.figure.size; ++i)
			{
				int tmp_pos_x, tmp_pos_y;

				tmp_pos_x = player.x + player.figure.recs[i].x;
				tmp_pos_y = player.y + player.figure.recs[i].y;


				//TODO: разобраться с этой структурой, может вытащить ее из класса?
				player.structure.x = tmp_pos_x * sector_size;
				player.structure.y = tmp_pos_y * sector_size;
				player.structure.width = sector_size;
				player.structure.height = sector_size;

				DrawRectangleRounded(player.structure, 0.5f, 1, player.figure.recs[i].color);
				DrawRectangleRoundedLines(player.structure, 0.5f, 1, 3.0f, player.figure.recs[i].outline_color);
			}

			// Отрисовка квадратов на уровне
			for (int i = 0; i < world.arr.size(); ++i)
			{
				player.structure.x = world.arr[i].x * sector_size;
				player.structure.y = world.arr[i].y * sector_size;
				player.structure.width = sector_size;
				player.structure.height = sector_size;

				DrawRectangleRounded(player.structure, 0.5f, 1, world.arr[i].color);
				DrawRectangleRoundedLines(player.structure, 0.5f, 1, 3.0f, world.arr[i].outline_color);
			}

			// Debug
			std::string debug = "pos "s + std::to_string(player.x) + ", " + std::to_string(player.y)
				+ "\n left: " + std::to_string(player.CanMove("left"))
				+ "\n right: " + std::to_string(player.CanMove("right"))
				+ "\n down: " + std::to_string(player.CanMove("down"))
				+ "\n map size: " + std::to_string(world.arr.size());
			DrawText(debug.c_str(), 10, 10, 30, RED);

		EndDrawing();
	}

	CloseWindow();
}