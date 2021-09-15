#pragma once

#include "figure.h"
#include "level.h"
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
	Level* world;
	Figure figure;

	explicit Player(Level* world);
	Player(Level* world, Figure::Figures figure);

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