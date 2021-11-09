#pragma once

#include <raylib.h>
#include <string>

#include "windowElementIntrface.h"

namespace Interface
{
	class Text : public WindowElementInterface
	{
	public:
		Text(const std::string& text,
			 int posX, int posY,
			 int FontSize = 40,
			 Color color = BLACK,
			 HA posHAlign = HA::LEFT,
			 VA posVAlign = VA::TOP,
			 HA textHAlign = HA::CENTER,
			 VA textVAlign = VA::CENTER);

		void update(const ElementArgs& args) override;

	private:
		std::string text_;
		Font font_ = GetFontDefault();
		float spacing_ = 5.0f;
		int posX_;
		int posY_;
		int fontSize_;
		HA posHAlign_;
		VA posVAlign_;
		HA textHAlign_;
		VA textVAlign_;
		Color color_;
	};
}