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

	World world = World(bound_x, bound_y);
	Player player = Player(&world);

	float pos_y = 0;
	while (!WindowShouldClose())
	{
		using namespace std::string_literals; // для ""s

		float dt{ GetFrameTime() };
		float speed{ 0.0f };

		// Управление движением
		if (IsKeyDown(KEY_DOWN))
			speed = 10.0f;
		else
			speed = 2.5f;
		
		pos_y += speed * dt;
		player.y = pos_y;

		if (player.CanMove("down"))
			player.y = pos_y;
		else
			pos_y = 0.0f;

		
		if (IsKeyPressed(KEY_RIGHT) && player.CanMove("right") )
			player.x += 1;
		if (IsKeyPressed(KEY_LEFT) && player.CanMove("left"))
			player.x -= 1;
		if (IsKeyPressed(KEY_UP))
			player.RotateFigure();

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
			for (int i = 0; i < world.size; ++i)
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
					+ "\n left: " + std::to_string(player.CanMove("left"))
					+ "\n right: " + std::to_string(player.CanMove("right"))
					+ "\n down: " + std::to_string(player.CanMove("down"));
				DrawText(debug.c_str(), 10, 10, 30, RED);
			}

		EndDrawing();
	}

	CloseWindow();
}