#pragma once

#include <array>

#include "rectangle.h"
#include "figure.h"
#include "observer.h"

// Представляет собой игровой мир
class Level : public Observer
{
public:
	int size_x;
	int size_y;

private:
	std::array<Rec, 200> arr_;

public:
	Level(int bound_x, int bound_y);

	void clear();
	[[nodiscard]] uint64_t get_size() const;
	Rec& get_element(uint64_t index);
	bool is_element_occupied(int x, int y);

private:
	void set_element_by_position(int world_x, int world_y, Color color);
	void scan_for_complete_rows_and_call_clear_row();
	void clear_row(int row);
	void on_notify(void* entity, Events event) override;
};