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

	explicit Player(World* world);
	Player(World* world, figure_enum figure);

private:
	void load_figure_to_world_arr();
	void load_figure_to_world_arr2();
	void return_figure_to_start_position();

public:
	void change_figure(figure_enum figures);
	void change_figure_random();
	bool move_left();
	bool move_right();
	void fall(float dt);
	void speed_up();
	void speed_down();
	void rotate_figure();
};