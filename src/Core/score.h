#pragma once

#include "observer.h"
#include "graphics.h"

constexpr int FIGURE_REWARD = 15;
constexpr int ROW_REWARD = 100;

class Score : public Observer
{
public:
	void update(const GraphicsSystem& graphics) const
	{
		graphics.drawScore(score_);
	}

	void onNotify(void* entity, Events event)
	{
		if (event == Events::PLAYER_FELL)
		{
			score_ += FIGURE_REWARD;
		}
		if (event == Events::ROW_CLEARED)
		{
			score_ += ROW_REWARD;
		}
	}

private:
	int score_ = 0;
};