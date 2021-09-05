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
	std::array<Rec, 200> arr_;

public:
	World(int bound_x, int bound_y);

	void clear();
	[[nodiscard]] uint64_t get_size() const;
	Rec& get_element(uint64_t index);
	bool is_element_occupied(int x, int y);

	void set_element_by_position(int world_x, int world_y, Color color);
	void scan_for_complete_rows();

private:
	void clear_row(int row);
};