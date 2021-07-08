#include "world.h"

World::World(int bound_x, int bound_y)
	: bound_x{ bound_x }, bound_y{ bound_y }, arr{ }
{
	// TODO: Пофиксить месево, возможно заменить вектор на аррей лол
	size = bound_x * bound_y;
	arr.resize(size);
}

void World::ClearWorld()
{
	for (auto& elem : arr)
	{
		if(elem.is_occupied)
			elem = Rec();
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

void World::SetElement(Rec& element)
{
	// Переводим двумерный индекс массива в одномерный
	int element_number = element.x + element.y * bound_x;

	if(element_number <= arr.size())
		arr[element_number] = element;
	else
		throw("Element at this number doesn't exist");
}

// Обращение как к двумерному массиву
bool World::IsElementOccupied(int x, int y)
{
	if ((x >= 0 && x <= bound_x) && (y >= 0  && y <= bound_y))
		return arr[x + y * bound_x].is_occupied;
	else
		return false;
	
}

