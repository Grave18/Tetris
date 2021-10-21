#pragma once

#include <string>
#include <string_view>

#include <raylib.h>

class MenuSystem
{
public:
    MenuSystem(float screenWidth, float screenHeight)
        : screenWidth_(screenWidth), screenHeight_(screenHeight)
    { }

    // r prefix - 0.0f to 1.0f (relative to screen size)
    void text(const std::string_view& text, float rFontSize, float rX, float rY, const Color& color = BLACK) const
    {
        correctFloatRange01(rFontSize);
        correctFloatRange01(rX);
        correctFloatRange01(rY);

        Font font = GetFontDefault();
        const float spacing = screenWidth_ / 100.0f;
        const float fontSize = screenWidth_ * rFontSize;
        const Vector2 textSize = MeasureTextEx(font, text.data(), fontSize, spacing);
        const Vector2 position
        {
            screenWidth_* rX - textSize.x / 2.0f,
            screenHeight_* rY - textSize.y / 2.0f
        };

        DrawTextEx(font, text.data(), position, fontSize, spacing, color);
    }

    // r prefix - 0.0f to 1.0f (relative to screen size)
    void button(const std::string_view& text, float rFontSize, float rX, float rY, Rectangle& outBounds, const Vector2& mousePos, const Color& textColor = BLACK, const Color& frameColor = BLACK) const
    {
        correctFloatRange01(rFontSize);
        correctFloatRange01(rX);
        correctFloatRange01(rY);

        Font font = GetFontDefault();
        const float spacing = screenWidth_ / 100.0f;
        const float fontSize = screenWidth_ * rFontSize;
        const Vector2 textSize = MeasureTextEx(font, text.data(), fontSize, spacing);
        const Vector2 position
        {
            screenWidth_ * rX - textSize.x / 2.0f,
            screenHeight_ * rY - textSize.y / 2.0f
        };

        float playOffset = screenWidth_ / 100.0f;
        outBounds.x = position.x - playOffset;
        outBounds.y = position.y - playOffset;
        outBounds.width = textSize.x + playOffset * 2;
        outBounds.height = textSize.y + playOffset * 2;

        DrawTextEx(font, text.data(), position, fontSize, spacing, textColor);
        if (CheckCollisionPointRec(mousePos, outBounds))
            //TODO: magic number 5
            DrawRectangleLinesEx(outBounds, 5, frameColor); 
    }

    bool isButtonPressed(const Rectangle& buttonBounds, const Vector2& mousePos, bool isAnykeyPressed) const
    {
        if (CheckCollisionPointRec(mousePos, buttonBounds) && isAnykeyPressed)
            return true;

        return false;
    }

    // r prefix float must be 0.0f to 1.0f (relative to screen size)
    float scrollBar(float rX, float rY, float rWidth, float rHeight, Vector2 mousePos, bool isAnykeyPressed, float barSize = 1.0f, const Color& bodyColor = RED, const Color& frameColor = BLACK ) const
    {
        correctFloatRange01(rX);
        correctFloatRange01(rY);
        correctFloatRange01(rWidth);
        correctFloatRange01(rHeight);

        // TODO: alignments(centered, topleft)
        Rectangle bounds
        {
            screenWidth_ * rX - screenWidth_ *rWidth / 2.0f,
            screenHeight_ * rY - screenHeight_ * rHeight / 2.0f,
            screenWidth_ * rWidth,
            screenHeight_ * rHeight
        };

        // TODO: try make scrollBar class
        Rectangle bodyBounds = bounds;
        static float width = screenWidth_ * rWidth * barSize;
        if (CheckCollisionPointRec(mousePos, bounds) && isAnykeyPressed)
            width = mousePos.x - bounds.x;
        bodyBounds.width = width;

        DrawRectangleRec(bodyBounds, bodyColor);
        //TODO: 5
        DrawRectangleLinesEx(bounds, 5, frameColor);

        // normalize to 0.0f to 1.0f
        return width / screenWidth_ / rWidth;
    }

private:
    void correctFloatRange01(float& slider) const
    {
        if (slider > 1.0f) slider = 1.0f;
        else if (slider < 0.0f) slider = 0.0f;
    }

    float screenWidth_;
    float screenHeight_;
};

class Button
{

};