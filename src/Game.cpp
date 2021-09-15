/*
* This game is classic tetris, with figures with 4 components
* Coded with use of RayLib 3.7
* Rec - minimal component of figure and level
* Figure - controlled by player
*
* Эта игра классический тетрис, где фигура состоит из 4ч компонентов
* написана с помощью RayLib 3.7
* Rec(значит rectangle) - минимальная единица, из чего состоит фигура и уровень
* Figure(фигура) - то, чем управляет игрок
*/

#include "Game.h"

constexpr int level_width = 10;
constexpr int level_height = 20;
constexpr int sector_size = 50;
constexpr int scr_width = (level_width * sector_size) + 10 * sector_size;
constexpr int scr_height = level_height * sector_size;
const char* title = "Tetris";

static bool is_debugging = true;

int main()
{
	InitWindow(scr_width, scr_height, title);
	SetTargetFPS(60);

	Level level(level_width, level_height);
	Player player(&level);
	// Add observer for player reaches ground event
	player.fell_event().add_observer(&level);

	InputHandler input_handler;
	Command* command = nullptr;

	while (!WindowShouldClose())
	{
		// For using ""s
		using namespace std::string_literals;

		// DeltaTime
		const float dt = GetFrameTime();

		command = input_handler.HandleInput();
		if (command)
			command->Execute(player);

		player.fall(dt);

		if (IsKeyDown(KEY_DOWN))
			player.speed_up();
		if (IsKeyUp(KEY_DOWN))
			player.speed_down();

		// Debug control
		if (IsKeyPressed(KEY_D))
			is_debugging = !is_debugging;

		if (is_debugging)
		{
			if (IsKeyPressed(KEY_O))
				player.change_figure(Figure::Figures::O);
			else if (IsKeyPressed(KEY_I))
				player.change_figure(Figure::Figures::I);
			else if (IsKeyPressed(KEY_S))
				player.change_figure(Figure::Figures::S);
			else if (IsKeyPressed(KEY_Z))
				player.change_figure(Figure::Figures::Z);
			else if (IsKeyPressed(KEY_L))
				player.change_figure(Figure::Figures::L);
			else if (IsKeyPressed(KEY_J))
				player.change_figure(Figure::Figures::J);
			else if (IsKeyPressed(KEY_T))
				player.change_figure(Figure::Figures::T);

			if (IsKeyPressed(KEY_BACKSPACE))
				level.clear();
		}

		BeginDrawing();

		ClearBackground(RAYWHITE);

		// HUD
		Rectangle rec_struct{0, 0, level_width * sector_size, level_height * sector_size};
		// Level frame
		DrawRectangleLinesEx(rec_struct, 5, RED);

		// Score frame
		rec_struct = {level_width * sector_size + 10, 100, 300, 100};
		DrawRectangleLinesEx(rec_struct, 5, RED);

		DrawText("SCORE:", level_width * sector_size + 10, 0, 40, BLACK);
		DrawText("0", level_width * sector_size + 20, 125, 50, BLACK);

		// Next figure frame


		// Rendering of figure
		rec_struct.width = sector_size;
		rec_struct.height = sector_size;

		for (uint64_t i = 0; i < player.figure.size; ++i)
		{
			const int tmp_pos_x = player.x + player.figure[i].x;
			const int tmp_pos_y = player.y + player.figure[i].y;

			rec_struct.x = tmp_pos_x * sector_size;
			rec_struct.y = tmp_pos_y * sector_size;

			DrawRectangleRounded(rec_struct, 0.5f, 1, player.figure[i].color);
			DrawRectangleRoundedLines(rec_struct, 0.5f, 1, 3.0f, player.figure[i].outline_color);
		}

		// Rendering of level
		for (int y = 0; y < level.size_y; ++y)
		{
			for (int x = 0; x < level.size_x; ++x)
			{
				const Rec& element = level.get_element(x + y * level.size_x);
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
		if (is_debugging)
		{
			std::string debug = "FPS "s + std::to_string(GetFPS()) +
				"\npos "s + std::to_string(player.x) + ", " + std::to_string(player.y);
			DrawText(debug.c_str(), 10, 10, 30, DARKBLUE);
		}

		EndDrawing();
	}

	CloseWindow();
}
