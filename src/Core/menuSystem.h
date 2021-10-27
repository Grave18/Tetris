#pragma once

#include <string>
#include <string_view>
#include <raylib.h>

class MenuSystem
{
public:
    MenuSystem(int screenWidth, int screenHeight)
        : screenWidth_(static_cast<float>(screenWidth))
        , screenHeight_(static_cast<float>(screenHeight))
    { }

    void resize(int windowWidth, int windowHeight)
    {
        screenWidth_ = static_cast<float>(windowWidth);
        screenHeight_ = static_cast<float>(windowHeight);
    }

    // TODO: alignments(centered, topleft)
    
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
    bool button(const std::string_view& text, float rFontSize, float rX, float rY, const Vector2& mousePos, bool isPressed, const Color& textColor = BLACK, const Color& frameColor = BLACK) const
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

        float frameOffset = screenWidth_ / 130.0f;
        Rectangle bounds
        {
            position.x - frameOffset,
            position.y - frameOffset,
            textSize.x + frameOffset * 2,
            textSize.y + frameOffset * 2
        };

        // text
        DrawTextEx(font, text.data(), position, fontSize, spacing, textColor);

        // select frame
        const auto lineThick = static_cast<int>(screenWidth_ / 200.0f);
        if (CheckCollisionPointRec(mousePos, bounds))
            DrawRectangleLinesEx(bounds, lineThick, frameColor); 

        if (CheckCollisionPointRec(mousePos, bounds) && isPressed)
            return true;
        return false;
    }

    // TODO: try make scrollBar class
    // r prefix float must be 0.0f to 1.0f (relative to screen size)
    float scrollBar(float rX, float rY, float rWidth, float rHeight, Vector2 mousePos, bool isAnykeyPressed, float barSize = 1.0f, const Color& bodyColor = RED, const Color& frameColor = BLACK ) const
    {
        correctFloatRange01(rX);
        correctFloatRange01(rY);
        correctFloatRange01(rWidth);
        correctFloatRange01(rHeight);
        
        Rectangle bounds
        {
            screenWidth_ * rX - screenWidth_ *rWidth / 2.0f,
            screenHeight_ * rY - screenHeight_ * rHeight / 2.0f,
            screenWidth_ * rWidth,
            screenHeight_ * rHeight
        };
        Rectangle bodyBounds = bounds;
        static float width = rWidth * barSize;
        if (CheckCollisionPointRec(mousePos, bounds) && isAnykeyPressed)
            width = (mousePos.x - bounds.x) / screenWidth_;
        bodyBounds.width = width * screenWidth_;

        DrawRectangleRec(bodyBounds, bodyColor);
        
        const auto lineThick = static_cast<int>(screenWidth_ / 200.0f);
        DrawRectangleLinesEx(bounds, lineThick, frameColor);

        // normalize to 0.0f to 1.0f
        return width / rWidth;
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