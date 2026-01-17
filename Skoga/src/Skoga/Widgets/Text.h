#pragma once

#include "Skoga/Fonts.h"
#include "Skoga/Widget.h"
namespace Skoga
{
    enum class HorizontalAlignment
    {
        Left,
        Center,
        Right
    };

    enum class VerticalAlignment
    {
        Top,
        Middle,
        Bottom
    };

    class TextWidget : public Widget
    {
    public:
        TextWidget(const char* text, float fontSize = 16.0f, const char* fontName = FontSegoeui);

        void SetText(const char* text);
        void SetFontSize(float fontSize);
        void SetHorizontalAlignment(HorizontalAlignment alignment);
        void SetVerticalAlignment(VerticalAlignment alignment);
        void SetFontName(const char* fontName);

    protected:
        void DrawSelf(NVGcontext* vg) override;

    private:
        const char* m_Text;
        float m_FontSize;
        HorizontalAlignment m_HorizontalAlignment = HorizontalAlignment::Left;
        VerticalAlignment m_VerticalAlignment = VerticalAlignment::Top;
        const char* m_FontName = FontSegoeui;
    };
} // namespace Skoga