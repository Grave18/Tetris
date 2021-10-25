#pragma once

#include "observer.h"
#include "graphicsSystem.h"

class Score : public Observer
{
public:
	void clear()
	{
		score_ = 0;
	}

	void updateGraphics(const GraphicsSystem& graphics) const
	{
		graphics.drawScore(score_);
	}

	void onNotify(void* entity, Events event) override
	{
		if (event == Events::PLAYER_FELL)
		{
			score_ += FIGURE_REWARD;
		}
		else if (event == Events::ROW_CLEARED)
		{
			score_ += ROW_REWARD;
		}
	}

private:
	int score_ = 0;

	const static int FIGURE_REWARD = 15;
	const static int ROW_REWARD = 100;
};