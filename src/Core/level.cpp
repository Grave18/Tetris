#include "level.h"
#include <cassert>

#include "player.h"


Level::Level(int bound_x, int bound_y)
	: size_x{ bound_x }, size_y{ bound_y }, arr_{ }
{ 
}

// Очищает мир
void Level::clear()
{
	for (auto& element : arr_)
	{
		if (element.is_occupied)
			element.clear();
	}
}

// Возвращает размер массива мира
uint64_t Level::get_size() const
{
	return arr_.size();
}

// Пока не используется
Rec& Level::get_element(uint64_t index)
{
	if (index < arr_.size())
		return arr_[index];
	else
		throw("Element at this number doesn't exist");
}

// Обращение как к двумерному массиву
bool Level::is_element_occupied(int x, int y)
{
	if ((x >= 0 && x <= size_x) && (y >= 0 && y <= size_y))
		return arr_[x + y * size_x].is_occupied;
	else
		return false;
}

//private:

// Загружает элемент в массив карты
void Level::set_element_by_position(int world_x, int world_y, Color color)
{
	assert(world_x >= 0 && world_x < size_x);
	assert(world_y >= 0 && world_y < size_y);

	const int index = world_x + world_y * size_x;

	arr_[index].is_occupied = true;
	arr_[index].color = color;
}

void Level::scan_for_complete_rows_and_call_clear_row()
{
	for (int y = 0; y < size_y ; ++y)
	{
		int num_of_occupied = 0;

		for (int x = 0; x < size_x; ++x)
		{
			if (arr_[x + y * size_x].is_occupied)
				++num_of_occupied;
		}

		if (num_of_occupied == size_x)
			clear_row(y);
	}
}

// Заполняет ряд элементами, располагающимися выше по y на 1
void Level::clear_row(const int row)
{
	assert(row >= 0 && row < size_y && " row out of bounds");

	if (row == 0)
	{
		for (int x = 0; x < size_x; ++x)
		{
			// так как row = 0 индексом является просто x
			arr_[x].is_occupied = false;
		}
	}
	else
	{
		for (int x = 0; x < size_x; ++x)
		{
			// Копируем параметры верхнего элемента
			arr_[x + row * size_x].is_occupied = arr_[x + (row - 1) * size_x].is_occupied;
			arr_[x + row * size_x].color = arr_[x + (row - 1) * size_x].color;
		}

		clear_row(row - 1);
	}
}

void Level::on_notify(void* entity, Events event)
{
	if(event == Events::PLAYER_FELL_EVENT)
	{
		const auto player = static_cast<Player*>(entity);
		for(int i = 0; i < player->figure.size; ++i)
		{
			set_element_by_position(
				player->figure[i].x + player->x,
				player->figure[i].y + player->y,
				player->figure[i].color);
		}
		
		scan_for_complete_rows_and_call_clear_row();
	}
}

