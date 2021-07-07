#include "player.h"

Player::Player(World* world, FigureEnum figure)
	: x{ 0 }, y{ 0 }, world{ world }
{
	ChangeFigure(figure);
}

void Player::LoadToWorldArr()
{
	// Загружаем фигуру в массив карты
	for (int i = 0; i < figure.size; ++i)
	{
		Rec rec = Rec(figure[i]);
		// Переводим локальные координаты в глобальные
		rec.x += x;
		rec.y += y;
		rec.is_occupied = true;

		world->SetElement(rec);
	}
}

void Player::ChangeFigure(FigureEnum figures)
{
	if (figures == FigureEnum::O)
		figure = Figures::o;
	else if (figures == FigureEnum::I)
		figure = Figures::i;
	else if (figures == FigureEnum::S)
		figure = Figures::s;
	else if (figures == FigureEnum::Z)
		figure = Figures::z;
	else if (figures == FigureEnum::L)
		figure = Figures::l;
	else if (figures == FigureEnum::J)
		figure = Figures::j;
	else if (figures == FigureEnum::T)
		figure = Figures::t;
}

bool Player::CanMove(const char* direction)
{
	// Сканируем rec сверху вниз, слева направо
	for (int i = 0; i < figure.size; ++i)
	{
		// Координаты квадратов, переведенные в мировые
		int world_x = x + figure[i].x;
		int world_y = y + figure[i].y;

		// TODO: сделать перечисление up, down и тд.

		if ((direction == "right"))
		{
			if ((world_x + 1) >= world->bound_x || world->IsElementOccupied(world_x + 1, world_y))
			{
				return false;
			}
		}

		if (direction == "left")
		{
			if ((world_x - 1) < 0 || world->IsElementOccupied(world_x - 1, world_y))
			{
				return false;
			}
		}

		if (direction == "down")
		{
			if ((world_y + 1) >= world->bound_y || world->IsElementOccupied(world_x, world_y + 1))
			{
				LoadToWorldArr();

				// Возвращаем фигуру в начало
				x = 0;
				y = 0;

				return false;
			}
		}
	}

	return true;
}

void Player::RotateFigure()
{
	for (int i = 0; i < figure.size; ++i)
	{
		if(figure.figure_type != FigureEnum::O)
		{
			// Поворот левосторонней системы против часовой
			// x' =  x * cos(90) + y * sin(90)  // sin(90) = 1, cos(90) = 0;
			// y' = -x * sin(90) + y * cos(90)
			int x = figure[i].x;
			int y = figure[i].y;

			figure[i].x = y;
			figure[i].y = -x;
		}
	}
}