#pragma once

class ElementArgs
{
public:
	// difference between fixed and real resolution
	[[nodiscard]] float getMult() const { return mult_; }
	[[nodiscard]] float getFixedXRes() const { return fixedWindResX_; }
	[[nodiscard]] float getFixedYRes() const { return fixedWindResY_; }
	[[nodiscard]] float getXRes() const { return fixedWindResX_ * mult_; }
	[[nodiscard]] float getYRes() const { return fixedWindResY_ * mult_; }
	void findMultiplier(int screenWidth)
	{
		mult_ = screenWidth / fixedWindResX_;
	}

private:
	float mult_ = 0.0f;
	// horisontal resolution (width)
	float fixedWindResX_ = 1920.0f;
	// vertical resolution (height)
	float fixedWindResY_ = 1080.0f;
};
