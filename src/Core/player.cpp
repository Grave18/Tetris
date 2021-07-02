#include "player.h"

Player::Player(World* world, FigureEnum figure)
	: x{ 0 }, y{ 0 }, structure{ 0 }, world{ world }
{
	ChangeFigure(figure);
}

void Player::LoadToWorldArr()
{
	// ��������� ������ � ������ �����
	for (int i = 0; i < figure.size; ++i)
	{
		Rec rec = Rec(figure.recs[i]);
		rec.x += x;
		rec.y += y;

		//TODO: �������� �� �������� �� ������ ����� �� �������
		world->arr.push_back(rec);
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
	// ��������� rec ������ ����, ����� �������
	for (int i = 0; i < figure.size; ++i)
	{
		// ���������� ���������, ������������ � �������
		int world_x, world_y;

		world_x = x + figure.recs[i].x;
		world_y = y + figure.recs[i].y;

		// TODO: ������� ������������ up, down � ��.

		if ((direction == "right"))
		{
			if ((world_x + 1) >= world->bound_x)
			{
				return false;
			}

			for (int j = 0; j < world->arr.size(); ++j)
			{
				if ((world_x + 1) == world->arr[j].x && world_y == world->arr[j].y)
				{
					return false;
				}
			}
		}

		if (direction == "left")
		{
			if ((world_x - 1) < 0)
			{
				return false;
			}

			for (int j = 0; j < world->arr.size(); ++j)
			{
				if ((world_x - 1) == world->arr[j].x && world_y == world->arr[j].y)
				{
					return false;
				}
			}
		}

		if (direction == "down")
		{
			if ((world_y + 1) >= world->bound_y)
			{
				LoadToWorldArr();

				// ���������� ������ � ������
				x = 0;
				y = 0;

				return false;
			}

			for (int j = 0; j < world->arr.size(); ++j)
			{
				if (world_x == world->arr[j].x && (world_y + 1) == world->arr[j].y)
				{
					LoadToWorldArr();

					// ���������� ������ � ������
					x = 0;
					y = 0;

					return false;
				}
			}
		}
	}

	return true;
}