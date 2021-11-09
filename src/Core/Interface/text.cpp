#include "Interface/text.h"

namespace Interface
{
	Text::Text(const std::string& text,
		 int posX, int posY,
		 int FontSize,
		 Color color,
		 HA posHAlign,
		 VA posVAlign,
		 HA textHAlign,
		 VA textVAlign)
		 : text_(text)
		 , posX_(posX), posY_(posY)
		 , fontSize_(FontSize)
		 , color_(color)
		 , posHAlign_(posHAlign)
		 , posVAlign_(posVAlign)
		 , textHAlign_(textHAlign)
		 , textVAlign_(textVAlign)
	{

	}

	void Text::update(const ElementArgs& args)
	{
		// text and pos LEFT alignment assumed
		int posX = posX_ * args.getMult();
		// text and pos TOP alignment assumed
		int posY = posY_ * args.getMult();

		// position alignment
		if (posHAlign_ == HA::center)
		{
			posX += args.getXRes() / 2.0f;
		}
		else if (posHAlign_ == HA::right)
		{
			posX += args.getXRes();
		}

		if (posVAlign_ == VA::center)
		{
			posY += args.getYRes() / 2.0f;
		}
		else if (posVAlign_ == VA::bottom)
		{
			posY += args.getYRes();
		}
		
		// text alignment
		const float spacing =  spacing_ * args.getMult();
		const int fontSize = fontSize_ * args.getMult();
		const Vector2 textSize = MeasureTextEx(font_, text_.c_str(), fontSize, spacing);

		if (textHAlign_ == HA::center)
		{
			posX -= textSize.x / 2.0f;
		}
		else if (textHAlign_ == HA::right)
		{
			posX -= textSize.x;
		}
		
		if (textVAlign_ == VA::center)
		{
			posY -= textSize.y / 2.0f;
		}
		else if (textVAlign_ == VA::bottom)
		{
			posY -= textSize.y;
		}

		Vector2 position {posX, posY};

		DrawTextEx(font_, text_.c_str(), position, fontSize, spacing, color_);
	}
};