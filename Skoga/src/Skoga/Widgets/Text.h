#pragma once

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
        TextWidget(const char* text, float fontSize = 16.0f);

        void SetText(const char* text);
        void SetFontSize(float fontSize);
        void SetHorizontalAlignment(HorizontalAlignment alignment);
        void SetVerticalAlignment(VerticalAlignment alignment);

    protected:
        void DrawSelf(NVGcontext* vg) override;

    private:
        const char* m_Text;
        float m_FontSize;
        HorizontalAlignment m_HorizontalAlignment = HorizontalAlignment::Left;
        VerticalAlignment m_VerticalAlignment = VerticalAlignment::Top;
    };
} // namespace Skoga