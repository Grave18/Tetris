#include "player.h"
#include "random_number.h"

Player::Player(World* world)
	: x{ 0 }, y{ 0 }, world{ world }, float_y{ 0.0f }, fall_speed{ 2.5f }
{
	ChangeFigureRandom();
	ReturnFigureToStartPosition();
}

Player::Player(World* world, FigureEnum figure)
	: x{ 0 }, y{ 0 }, world{ world }, float_y{ 0.0f }, fall_speed{ 2.5f }
{
	ChangeFigure(figure);
	ReturnFigureToStartPosition();
}

void Player::LoadFigureToWorldArr()
{
	//TODO: Все не так, надо заменить отправку объектов на отправку данных, наверно
	// Загружаем фигуру в массив карты
	for (int i = 0; i < figure.size; ++i)
	{
		world->SetElementByPosition(figure[i].x + x, figure[i].y + y, figure[i].color);
	}

	world->ScanForCompleteRows();
}

// Возвращаем фигуру в начало и меняем на рандомную
void Player::ReturnFigureToStartPosition()
{
	x = 4;
	y = 1;
	float_y = 1.0f;
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

void Player::ChangeFigureRandom()
{
	RandomNumber::ResetRandomNumber();
	ChangeFigure((FigureEnum)RandomNumber::GetRandomNumber(0, (int)FigureEnum::MAX_ELEMENT - 1));
}

// Двигает игрока, возвращает false если двигаться мешает препятствие
bool Player::MoveLeft()
{
	for (int i = 0; i < figure.size; ++i)
	{
		// Координаты квадратов фигуры, переведенные в мировые
		int world_x = x + figure[i].x;
		int world_y = y + figure[i].y;

		if ((world_x - 1) < 0 || world->IsElementOccupied(world_x - 1, world_y))
		{
			return false;
		}
	}

	--x; // Двигаем фигуру влево
	
	return true;
}

bool Player::MoveRight()
{
	// Сканируем фигуру сверху вниз, слева направо
	for (int i = 0; i < figure.size; ++i)
	{
		// Координаты квадратов фигуры, переведенные в мировые
		int world_x = x + figure[i].x;
		int world_y = y + figure[i].y;

		if ((world_x + 1) >= world->bound_x || world->IsElementOccupied(world_x + 1, world_y))
		{
			return false;
		}
	}

	++x; // Двигаем фигуру вправо

	return true;
}

void Player::Fall(float dt)
{
	for (int i = 0; i < figure.size; ++i)
	{
		// Координаты квадратов фигуры, переведенные в мировые
		int world_x = x + figure[i].x;
		int world_y = y + figure[i].y;

		if ((world_y + 1) >= world->bound_y || world->IsElementOccupied(world_x, world_y + 1))
		{
			LoadFigureToWorldArr();
			ChangeFigureRandom();
			ReturnFigureToStartPosition();

			return;
		}
	}
	// Обеспечиваем плавное движение
	float_y += fall_speed * 1 / 60;
	y = static_cast<int>(float_y);
}

void Player::SpeedUp()
{
	fall_speed = 10.0f;
}

void Player::SpeedDown()
{
	fall_speed = 2.5f;
}

void Player::RotateFigure()
{
	if (figure.figure_type != FigureEnum::O && (x - 1) > -1 && (x + 1) < world->bound_x)
	{
		for (int i = 0; i < figure.size; ++i)
		{
		
			// Поворот левосторонней системы против часовой
			// x' =  x * cos(90) + y * sin(90)  // sin(90) = 1, cos(90) = 0;
			// y' = -x * sin(90) + y * cos(90)
			int local_x = figure[i].y;
			int local_y = -figure[i].x;
			
			figure[i].x = local_x;
			figure[i].y = local_y;
		}
	}
}