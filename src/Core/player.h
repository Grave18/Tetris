#pragma once

#include "figure.h"
#include "figures.h"
#include "figure_enum.h"
#include "world.h"

class Player
{
public:
	int x;
	int y;
	World* world;
	Figure figure;

	Player(World* world, FigureEnum figure);

private:
	void LoadToWorldArr();

public:
	void ChangeFigure(FigureEnum figures);
	bool CanMove(const char* direction);
	void RotateFigure();
};