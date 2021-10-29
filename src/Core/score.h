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
			score_ += figureReward_;
		}
		else if (event == Events::ROW_CLEARED)
		{
			score_ += rowReward_;
		}
	}

	int getScore() const { return score_; }

private:
	int score_ = 0;

	const int figureReward_ = 15;
	const int rowReward_ = 100;

	Subject observers_;
};