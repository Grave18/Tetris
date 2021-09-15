#include <raylib.h>

#include "player.h"


Player::Player(Level* world)
	: float_y_{0.0f}, fall_speed_{2.5f}, x{0}, y{0}, world{world}
{
	change_figure_random();
	return_figure_to_start_position();
}

Player::Player(Level* world, Figure::Figures figure)
	: float_y_{0.0f}, fall_speed_{2.5f}, x{0}, y{0}, world{world}
{
	change_figure(figure);
	return_figure_to_start_position();
}

// Возвращаем фигуру в начало и меняем на рандомную
void Player::return_figure_to_start_position()
{
	x = 4;
	y = 1;
	float_y_ = 1.0f;
}

Subject& Player::fell_event()
{
	return subject_;
}

void Player::change_figure(const Figure::Figures figures)
{
	if (figures == Figure::Figures::O)
		figure = Figure::o;
	else if (figures == Figure::Figures::I)
		figure = Figure::i;
	else if (figures == Figure::Figures::S)
		figure = Figure::s;
	else if (figures == Figure::Figures::Z)
		figure = Figure::z;
	else if (figures == Figure::Figures::L)
		figure = Figure::l;
	else if (figures == Figure::Figures::J)
		figure = Figure::j;
	else if (figures == Figure::Figures::T)
		figure = Figure::t;
}

void Player::change_figure_random()
{
	change_figure( 
		static_cast<Figure::Figures>(
			GetRandomValue(
	0, static_cast<int>(Figure::Figures::MAX_ELEMENT) - 1)));
}

// Двигает игрока, возвращает false если двигаться мешает препятствие
bool Player::move_left()
{
	for (int i = 0; i < figure.size; ++i)
	{
		// Координаты квадратов фигуры, переведенные в мировые
		const int world_x = x + figure[i].x;
		const int world_y = y + figure[i].y;

		if ((world_x - 1) < 0 || world->is_element_occupied(world_x - 1, world_y))
		{
			return false;
		}
	}

	--x; // Двигаем фигуру влево

	return true;
}

bool Player::move_right()
{
	// Сканируем фигуру сверху вниз, слева направо
	for (int i = 0; i < figure.size; ++i)
	{
		// Координаты квадратов фигуры, переведенные в мировые
		const int world_x = x + figure[i].x;
		const int world_y = y + figure[i].y;

		if ((world_x + 1) >= world->size_x || world->is_element_occupied(world_x + 1, world_y))
		{
			return false;
		}
	}

	++x; // Двигаем фигуру вправо

	return true;
}

void Player::fall(float dt)
{
	for (int i = 0; i < figure.size; ++i)
	{
		// Координаты квадратов фигуры, переведенные в мировые
		const int world_x = x + figure[i].x;
		const int world_y = y + figure[i].y;

		if ((world_y + 1) >= world->size_y || world->is_element_occupied(world_x, world_y + 1))
		{
			subject_.notify(this, Events::PLAYER_FELL_EVENT);
			change_figure_random();
			return_figure_to_start_position();

			return;
		}
	}
	// Обеспечиваем плавное движение
	float_y_ += fall_speed_ * 1 / 60;
	y = static_cast<int>(float_y_);
}

void Player::speed_up()
{
	fall_speed_ = 10.0f;
}

void Player::speed_down()
{
	fall_speed_ = 2.5f;
}

void Player::rotate_figure()
{
	if (figure.figure_type != Figure::Figures::O && (x - 1) > -1 && (x + 1) < world->size_x)
	{
		for (int i = 0; i < figure.size; ++i)
		{
			// Поворот левосторонней системы против часовой
			// x' =  x * cos(90) + y * sin(90)  // sin(90) = 1, cos(90) = 0;
			// y' = -x * sin(90) + y * cos(90)
			const int local_x = figure[i].y;
			const int local_y = -figure[i].x;

			figure[i].x = local_x;
			figure[i].y = local_y;
		}
	}
}
