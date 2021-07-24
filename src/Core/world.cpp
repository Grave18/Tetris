#include "world.h"
#include <cassert>


World::World(int bound_x, int bound_y)
	: bound_x{ bound_x }, bound_y{ bound_y }, arr{ }
{ 
}

void World::ClearWorld()
{
	for (auto& element : arr)
	{
		if (element.is_occupied)
			element.Clear();
	}
}

int World::GetSize()
{
	return arr.size();
}

// Пока не используется
Rec& World::GetElement(int element)
{
	if (element <= arr.size())
		return arr[element];
	else
		throw("Element at this number doesn't exist");
}

// Обращение как к двумерному массиву
bool World::IsElementOccupied(int x, int y)
{
	if ((x >= 0 && x <= bound_x) && (y >= 0 && y <= bound_y))
		return arr[x + y * bound_x].is_occupied;
	else
		return false;
}

// Загружает элемент в массив карты
void World::SetElementByPosition(int world_x, int world_y, Color color)
{
	assert(world_x >= 0 && world_x < bound_x);
	assert(world_y >= 0 && world_y < bound_y);

	int index = world_x + world_y * bound_x;

	arr[index].is_occupied = true;
	arr[index].color = color;
}

void World::ScanForCompleteRows()
{
	for (int y = bound_y - 1; y >= 0 ; --y)
	{
		int num_of_occupied = 0;

		for (int x = 0; x < bound_x; ++x)
		{
			if (arr[x + y * bound_x].is_occupied)
				++num_of_occupied;
		}

		if (num_of_occupied == bound_x)
			ClearRow(y);
	}
}

// Заполняет ряд элементами, распологающимися выше по y на 1
void World::ClearRow(int row)
{
	assert(row >= 0 && row < bound_y && " row out of bounds");

	if (row == 0)
	{
		for (int x = 0; x < bound_x; ++x)
		{
			// так как row = 0 индесом является просто x
			arr[x].is_occupied = false;
		}
	}
	else
	{
		for (int x = 0; x < bound_x; ++x)
		{
			// Копируем параметры верхнего элемента
			arr[x + row * bound_x].is_occupied = arr[x + (row - 1) * bound_x].is_occupied;
			arr[x + row * bound_x].color = arr[x + (row - 1) * bound_x].color;
		}

		ClearRow(row - 1);
	}


}

