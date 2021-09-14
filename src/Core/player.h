#pragma once

#include "figure.h"
#include "world.h"
#include "observer.h"

class Player
{
private:
	// Костыль, для обеспечения плавного движения вниз
	float float_y_;
	float fall_speed_;
	// шаблон Observer
	Subject subject_;

public:
	int x;
	int y;
	World* world;
	Figure figure;

	explicit Player(World* world);
	Player(World* world, Figure::Figures figure);

private:
	void return_figure_to_start_position();

public:
	Subject& fell_event(); 
	void change_figure(Figure::Figures figures);
	void change_figure_random();
	bool move_left();
	bool move_right();
	void fall(float dt);
	void speed_up();
	void speed_down();
	void rotate_figure();
};