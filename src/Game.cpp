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

static bool isDebugging = true;

int main()
{
	InitWindow(scr_width, scr_height, title);
	SetTargetFPS(60);
	
	int bound_x = scr_width / sector_size;
	int bound_y = scr_height / sector_size;
	const int world_size = level_width * level_height;

	World world(bound_x, bound_y);
	Player player(&world);

	InputHandler input_hendler;
	Command* command = nullptr;

	while (!WindowShouldClose())
	{
		using namespace std::string_literals; // для ""s
		
		float dt{ GetFrameTime() }; // deltaTime
		
		command = input_hendler.HandleInput();
		if (command)
			command->Execute(player);
		
		player.Fall(dt);

		if (IsKeyDown(KEY_DOWN))
			player.SpeedUp();
		if (IsKeyUp(KEY_DOWN))
			player.SpeedDown();

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
			/*for (int i = 0; i < world.GetSize(); ++i)
			{
				Rec& element = world.GetElement(i);
				if(element.is_occupied)
				{
					rec_struct.x = element.x * sector_size;
					rec_struct.y = element.y * sector_size;

					DrawRectangleRounded(rec_struct, 0.5f, 1, element.color);
					DrawRectangleRoundedLines(rec_struct, 0.5f, 1, 3.0f, element.outline_color);
				}
			}*/

			// Отрисовка элементов уровня 2
			for (int y = 0; y < world.bound_y; ++y)
			{
				for (int x = 0; x < world.bound_x; ++x)
				{
					Rec& element = world.GetElement(x + y * world.bound_x);
					if (element.is_occupied)
					{
						rec_struct.x = x * sector_size;
						rec_struct.y = y * sector_size;

						DrawRectangleRounded(rec_struct, 0.5f, 1, element.color);
						DrawRectangleRoundedLines(rec_struct, 0.5f, 1, 3.0f, element.outline_color);
					}
				}
			}

			// Debug
			if(isDebugging)
			{
				std::string debug = "FPS "s + std::to_string(GetFPS()) + 
									"\npos "s + std::to_string(player.x) + ", " + std::to_string(player.y) +
									"\narr[0,0] = " + std::to_string(world.arr[0].is_occupied)
									;
				DrawText(debug.c_str(), 10, 10, 30, RED);

				//system("cls");
				//
				//for (int y = 0; y < world.bound_y; ++y)
				//{
				//	bool is_occ = false;
				//	for (int x = 0; x < world.bound_x; ++x)
				//	{
				//		//std::cout << world.GetElement(x + y * world.bound_x).is_occupied << " ";
				//	}
				//	std::cout << "\n";
				//}
			}

		EndDrawing();
	}

	CloseWindow();
}