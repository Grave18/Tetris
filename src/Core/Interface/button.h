#pragma once
#include "Interface/windowElementIntrface.h"

namespace Interface
{
	class Button //: public WindowElementInterface
	{
	public:
		Button() = default;
		Button(Button&) = delete;
		Button(Button&&) = delete;
		Button& operator=(Button&) = delete;
		Button& operator=(Button&&) = delete;

		//void update(float multiplier_) override;

	private:


	};
}