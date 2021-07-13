#pragma once

#include <vector>

#include "rectangle.h"
#include "figure.h"

// Представляет собой игровой мир
class World
{
public:
	int bound_x;
	int bound_y;
	unsigned int size;

private:
	std::vector<Rec> arr;
	std::vector<int> row_element_count;

public:
	World(int bound_x, int bound_y);

	void ClearWorld();
	void SetElement(const Rec &element);
	void SetElementByPosition(int world_x, int world_y, Color color);
	Rec& GetElement(int element);
	bool IsElementOccupied(int x, int y);

	void ScanForCompleteRows();
	void ClearRow(int row);
};