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
	std::array<Rec, 200> arr;

public:
	World(int bound_x, int bound_y);

	void ClearWorld();
	void SetElement(const Rec &element);
	void SetElementByPosition(int world_x, int world_y, Color color);
	Rec& GetElement(int element);
	bool IsElementOccupied(int x, int y);
	int GetSize();

	void ScanForCompleteRows();
	void ClearRow(int row);
};