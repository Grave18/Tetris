#include "world.h"

World::World(int bound_x, int bound_y)
	: bound_x{ bound_x }, bound_y{ bound_y }, arr{ }
{
	// TODO: Пофиксить месево, возможно заменить вектор на аррей
	size = bound_x * bound_y;
	arr.resize(size);
}

void World::SetElement(Rec& element)
{
	// Переводим двумерный индекс массида в одномерный
	arr[static_cast<long long>(element.x) + static_cast<long long>(element.y) * static_cast<long long>(bound_x)] = element;
}

// Обращение как к двумерному массиву
Rec& World::GetElement(unsigned int x, unsigned int y)
{
	return arr[static_cast<long long>(x) + static_cast<long long>(y) * static_cast<long long>(bound_x)];
}

// Обращение как к одномерному массиву
Rec& World::GetElement(unsigned int element)
{
	return arr[element];
}