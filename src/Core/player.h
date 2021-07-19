#pragma once

#include "figure.h"
#include "figures.h"
#include "figure_enum.h"
#include "world.h"

class Player
{
private:
	// Костыль, для обеспечения плавного движения вниз
	float float_y;
	float fall_speed;
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
	bool MoveLeft();
	bool MoveRight();
	void Fall(float dt);
	void SpeedUp();
	void SpeedDown();
	void RotateFigure();
};