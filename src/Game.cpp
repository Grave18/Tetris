/*
* Эта игра классический тетрис, написана с помощью RayLib 3.8
* Rec(значит rectangle) - минимальная единица, из чего состоит фигура и уровень
* Figure(фигура) - то, чем управляет игрок
*/ 

#include "Game.h"

const int level_width = 10;
const int level_height = 20;
const int sector_size = 50;
const int scr_width = level_width * sector_size;
const int scr_height = level_height * sector_size;
const char* title =  "Tetris";

static bool isDebugging = false;

int main()
{
	InitWindow(scr_width, scr_height, title);
	SetTargetFPS(60);
	
	int bound_x = scr_width / sector_size;
	int bound_y = scr_height / sector_size;
	const int world_size = level_width * level_height;

	World world(bound_x, bound_y);
	Player player(&world);

	float pos_y = 0;
	while (!WindowShouldClose())
	{
		using namespace std::string_literals; // для ""s

		float dt{ GetFrameTime() };
		float speed{ 0.0f };

		if (IsKeyDown(KEY_DOWN))
			player.SpeedUp();
		if(IsKeyUp(KEY_DOWN))
			player.SpeedDown();

		InputHandler input_hendler;
		Command* command = input_hendler.HandleInput();
		if (command)
		{
			command->Execute(player);
		}
		
		player.Fall(dt);

		// Debug управление
		if (IsKeyPressed(KEY_D))
			isDebugging = !isDebugging;

		if(isDebugging)
		{
			if (IsKeyPressed(KEY_O))
				player.ChangeFigure(FigureEnum::O);
			else if (IsKeyPressed(KEY_I))
				player.ChangeFigure(FigureEnum::I);
			else if (IsKeyPressed(KEY_S))
				player.ChangeFigure(FigureEnum::S);
			else if (IsKeyPressed(KEY_Z))
				player.ChangeFigure(FigureEnum::Z);
			else if (IsKeyPressed(KEY_L))
				player.ChangeFigure(FigureEnum::L);
			else if (IsKeyPressed(KEY_J))
				player.ChangeFigure(FigureEnum::J);
			else if (IsKeyPressed(KEY_T))
				player.ChangeFigure(FigureEnum::T);

			if (IsKeyPressed(KEY_BACKSPACE))
				world.ClearWorld();
		}

		BeginDrawing();

			ClearBackground(RAYWHITE);

			Rectangle rec_struct{};
			rec_struct.width = sector_size;
			rec_struct.height = sector_size;

			// Отрисовка элементов фигуры
			for (int i = 0; i < player.figure.size; ++i)
			{
				int tmp_pos_x = player.x + player.figure[i].x;
				int tmp_pos_y = player.y + player.figure[i].y;

				rec_struct.x = tmp_pos_x * sector_size;
				rec_struct.y = tmp_pos_y * sector_size;

				DrawRectangleRounded(rec_struct, 0.5f, 1, player.figure[i].color);
				DrawRectangleRoundedLines(rec_struct, 0.5f, 1, 3.0f, player.figure[i].outline_color);
			}
			
			// Отрисовка элементов уровня
			for (int i = 0; i < world.GetSize(); ++i)
			{
				if(world.GetElement(i).is_occupied)
				{
					Rec rec = Rec(world.GetElement(i));

					rec_struct.x = rec.x * sector_size;
					rec_struct.y = rec.y * sector_size;

					DrawRectangleRounded(rec_struct, 0.5f, 1, rec.color);
					DrawRectangleRoundedLines(rec_struct, 0.5f, 1, 3.0f, rec.outline_color);
				}
			}

			// Debug
			if(isDebugging)
			{
				std::string debug = "pos "s + std::to_string(player.x) + ", " + std::to_string(player.y)
					+ "\n left: " + std::to_string(player.MoveLeft())
					+ "\n right: " + std::to_string(player.MoveRight());
				DrawText(debug.c_str(), 10, 10, 30, RED);
			}

		EndDrawing();
	}

	CloseWindow();
}