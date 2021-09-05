#include "player.h"
#include "random_number.h"

Player::Player(World* world)
	: float_y{0.0f}, fall_speed{2.5f}, x{0}, y{0}, world{world}
{
	change_figure_random();
	return_figure_to_start_position();
}

Player::Player(World* world, figure_enum figure)
	: float_y{0.0f}, fall_speed{2.5f}, x{0}, y{0}, world{world}
{
	change_figure(figure);
	return_figure_to_start_position();
}

void Player::load_figure_to_world_arr()
{
	//TODO: Все не так, надо заменить отправку объектов на отправку данных, наверно
	// Загружаем фигуру в массив карты
	for (int i = 0; i < figure.size; ++i)
	{
		world->set_element_by_position(figure[i].x + x, figure[i].y + y, figure[i].color);
	}

	world->scan_for_complete_rows();
}

// Возможно будет заменой
void Player::load_figure_to_world_arr2()
{
	//TODO: Все не так, надо заменить отправку объектов на отправку данных, наверно
	// Загружаем фигуру в массив карты
	for (int i = 0; i < figure.size; ++i)
	{
		world->set_element_by_position(figure[i].x + x, figure[i].y + y, figure[i].color);
	}

	world->scan_for_complete_rows();
}

// Возвращаем фигуру в начало и меняем на рандомную
void Player::return_figure_to_start_position()
{
	x = 4;
	y = 1;
	float_y = 1.0f;
}

void Player::change_figure(const figure_enum figures)
{
	if (figures == figure_enum::O)
		figure = Figures::o;
	else if (figures == figure_enum::I)
		figure = Figures::i;
	else if (figures == figure_enum::S)
		figure = Figures::s;
	else if (figures == figure_enum::Z)
		figure = Figures::z;
	else if (figures == figure_enum::L)
		figure = Figures::l;
	else if (figures == figure_enum::J)
		figure = Figures::j;
	else if (figures == figure_enum::T)
		figure = Figures::t;
}

void Player::change_figure_random()
{
	RandomNumber::reset_random_number();
	change_figure(
		static_cast<figure_enum>(RandomNumber::get_random_number(0, static_cast<int>(figure_enum::MAX_ELEMENT) - 1)));
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

		if ((world_x + 1) >= world->bound_x || world->is_element_occupied(world_x + 1, world_y))
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

		if ((world_y + 1) >= world->bound_y || world->is_element_occupied(world_x, world_y + 1))
		{
			load_figure_to_world_arr();
			change_figure_random();
			return_figure_to_start_position();

			return;
		}
	}
	// Обеспечиваем плавное движение
	float_y += fall_speed * 1 / 60;
	y = static_cast<int>(float_y);
}

void Player::speed_up()
{
	fall_speed = 10.0f;
}

void Player::speed_down()
{
	fall_speed = 2.5f;
}

void Player::rotate_figure()
{
	if (figure.figure_type != figure_enum::O && (x - 1) > -1 && (x + 1) < world->bound_x)
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
