#pragma once

#include <vector>

#include "rectangle.h"

// ѕредставл€ет собой игровое пространство
class World
{
public:
	int bound_x;
	int bound_y;
	unsigned int size;

private:
	std::vector<Rec> arr;

public:
	World(int bound_x, int bound_y);

	void SetElement(Rec& element);
	Rec& GetElement(unsigned int x, unsigned int y);
	Rec& GetElement(unsigned int element);
};