#pragma once

#include <vector>

#include "rectangle.h"

// Представляет собой игровое пространство
class World
{
public:
	int bound_x;
	int bound_y;

	std::vector<Rec> arr;

	World(int bound_x, int bound_y);
};