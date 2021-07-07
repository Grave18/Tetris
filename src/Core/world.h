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


	void ClearWorld();
	void SetElement(Rec& element);
	Rec& GetElement(int element);
	bool IsElementOccupied(int x, int y);
};