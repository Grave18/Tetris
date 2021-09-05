#include "world.h"
#include <cassert>


World::World(int bound_x, int bound_y)
	: bound_x{ bound_x }, bound_y{ bound_y }, arr_{ }
{ 
}

// Очищает мир
void World::clear_world()
{
	for (auto& element : arr_)
	{
		if (element.is_occupied)
			element.clear();
	}
}

size_t World::get_size() const
{
	return arr_.size();
}

// Пока не используется
Rec& World::get_element(size_t element)
{
	if (element <= arr_.size())
		return arr_[element];
	else
		throw("Element at this number doesn't exist");
}

// Обращение как к двумерному массиву
bool World::is_element_occupied(int x, int y)
{
	if ((x >= 0 && x <= bound_x) && (y >= 0 && y <= bound_y))
		return arr_[x + y * bound_x].is_occupied;
	else
		return false;
}

// Загружает элемент в массив карты
void World::set_element_by_position(int world_x, int world_y, Color color)
{
	assert(world_x >= 0 && world_x < bound_x);
	assert(world_y >= 0 && world_y < bound_y);

	const int index = world_x + world_y * bound_x;

	arr_[index].is_occupied = true;
	arr_[index].color = color;
}

void World::scan_for_complete_rows()
{
	for (int y = bound_y - 1; y >= 0 ; --y)
	{
		int num_of_occupied = 0;

		for (int x = 0; x < bound_x; ++x)
		{
			if (arr_[x + y * bound_x].is_occupied)
				++num_of_occupied;
		}

		if (num_of_occupied == bound_x)
			clear_row(y);
	}
}

// Заполняет ряд элементами, располагающимися выше по y на 1
void World::clear_row(int row)
{
	assert(row >= 0 && row < bound_y && " row out of bounds");

	if (row == 0)
	{
		for (int x = 0; x < bound_x; ++x)
		{
			// так как row = 0 индексом является просто x
			arr_[x].is_occupied = false;
		}
	}
	else
	{
		for (int x = 0; x < bound_x; ++x)
		{
			// Копируем параметры верхнего элемента
			arr_[x + row * bound_x].is_occupied = arr_[x + (row - 1) * bound_x].is_occupied;
			arr_[x + row * bound_x].color = arr_[x + (row - 1) * bound_x].color;
		}

		clear_row(row - 1);
	}


}

