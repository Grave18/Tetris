#include "world.h"


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

// Обращение как к одномерному массиву
Rec& World::GetElement(int element)
{
	if (element <= arr.size())
		return arr[element];
	else
		throw("Element at this number doesn't exist");
}

void World::SetElement(const Rec &element)
{
	// Переводим двумерный индекс массива в одномерный
	int element_number = element.x + element.y * bound_x;

	if(element_number <= arr.size())
		arr[element_number] = element;
	else
		throw("Element at this number doesn't exist");
}

// Загружает элемент в массив карты
void World::SetElementByPosition(int world_x, int world_y, Color color)
{
	int index = world_x + world_y * bound_x;

	if(index < arr.size() && !arr[index].is_occupied)
	{
		arr[index].x = world_x;
		arr[index].y = world_y;
		arr[index].is_occupied = true;
		arr[index].color = color;
	}
	else
		throw("Element at this number doesn't exist or already occupied");
}

// Обращение как к двумерному массиву
bool World::IsElementOccupied(int x, int y)
{
	if ((x >= 0 && x <= bound_x) && (y >= 0  && y <= bound_y))
		return arr[x + y * bound_x].is_occupied;
	else
		return false;
}

void World::ScanForCompleteRows()
{
	for (int y = 0; y < bound_y; ++y)
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

int World::GetSize()
{
	return arr.size();
}

// Заполняет ряд элементами, распологающимися выше по y на 1
void World::ClearRow(int row)
{
	if (row - 1 >= 0)
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

