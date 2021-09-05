/*
* Эта игра классический тетрис, написана с помощью RayLib 3.8
* Rec(значит rectangle) - минимальная единица, из чего состоит фигура и уровень
* Figure(фигура) - то, чем управляет игрок
*/ 

#include "Game.h"

constexpr int level_width = 10;
constexpr int level_height = 20;
constexpr int sector_size = 50;
constexpr int scr_width = (level_width * sector_size) + 10 * sector_size;
constexpr int scr_height = level_height * sector_size;
const char* title =  "Tetris";

static bool is_debugging = true;

int main()
{
	InitWindow(scr_width, scr_height, title);
	SetTargetFPS(60);

	constexpr int bound_x = level_width;
	constexpr int bound_y = level_height;

	World world(bound_x, bound_y);
	Player player(&world);

	InputHandler input_handler;
	Command* command = nullptr;

	while (!WindowShouldClose())
	{
		using namespace std::string_literals; // для ""s
		
		float dt{ GetFrameTime() }; // deltaTime
		
		command = input_handler.HandleInput();
		if (command)
			command->Execute(player);
		
		player.fall(dt);

		if (IsKeyDown(KEY_DOWN))
			player.speed_up();
		if (IsKeyUp(KEY_DOWN))
			player.speed_down();

		// Debug управление
		if (IsKeyPressed(KEY_D))
			is_debugging = !is_debugging;

		if(is_debugging)
		{
			if (IsKeyPressed(KEY_O))
				player.change_figure(figure_enum::O);
			else if (IsKeyPressed(KEY_I))
				player.change_figure(figure_enum::I);
			else if (IsKeyPressed(KEY_S))
				player.change_figure(figure_enum::S);
			else if (IsKeyPressed(KEY_Z))
				player.change_figure(figure_enum::Z);
			else if (IsKeyPressed(KEY_L))
				player.change_figure(figure_enum::L);
			else if (IsKeyPressed(KEY_J))
				player.change_figure(figure_enum::J);
			else if (IsKeyPressed(KEY_T))
				player.change_figure(figure_enum::T);

			if (IsKeyPressed(KEY_BACKSPACE))
				world.clear_world();
		}

		BeginDrawing();

			ClearBackground(RAYWHITE);

			// Рамки и тд.
			Rectangle rec_struct{ 0, 0, level_width * sector_size, level_height * sector_size };
			// Рамка вокруг мира
			DrawRectangleLinesEx(rec_struct, 5, RED);

			// Рамка счета
			rec_struct = { level_width * sector_size + 10, 100, 300, 100 };
			DrawRectangleLinesEx(rec_struct, 5, RED);

			DrawText("SCORE:", level_width * sector_size + 10, 0, 40, BLACK);
			DrawText("0", level_width * sector_size + 20, 125, 50, BLACK);

			// Рамка следующей фигуры


			// Отрисовка элементов фигуры
			rec_struct.width = sector_size;
			rec_struct.height = sector_size;

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
			for (int y = 0; y < world.bound_y; ++y)
			{
				for (int x = 0; x < world.bound_x; ++x)
				{
					const Rec& element = world.get_element(x + y * world.bound_x);
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
			if(is_debugging)
			{
				std::string debug = "FPS "s + std::to_string(GetFPS()) + 
									"\npos "s + std::to_string(player.x) + ", " + std::to_string(player.y)
									;
				DrawText(debug.c_str(), 10, 10, 30, DARKBLUE);
			}

		EndDrawing();
	}

	CloseWindow();
}