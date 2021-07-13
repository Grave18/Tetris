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

	Player(World* world);
	Player(World* world, FigureEnum figure);

private:
	void LoadFigureToWorldArr();
	void ReturnFigureToStartPosition();

public:
	void ChangeFigure(FigureEnum figures);
	void ChangeFigureRandom();
	bool CanMove(const char* direction);
	void RotateFigure();
};