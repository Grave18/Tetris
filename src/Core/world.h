#pragma once

#include <array>

#include "rectangle.h"
#include "figure.h"

// Представляет собой игровой мир
class World
{
public:
	int bound_x;
	int bound_y;

private:
	std::array<Rec, 72> arr;

public:
	World(int bound_x, int bound_y);

	void ClearWorld();
	int GetSize();
	Rec& GetElement(int element);
	bool IsElementOccupied(int x, int y);

	void SetElementByPosition(int world_x, int world_y, Color color);
	void ScanForCompleteRows();
	void ClearRow(int row);
};