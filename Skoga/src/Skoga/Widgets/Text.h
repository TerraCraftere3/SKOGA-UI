#pragma once

#include "Skoga/Color.h"
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
        TextWidget(const char* text);

        void SetText(const char* text);
        void SetHorizontalAlignment(HorizontalAlignment alignment);
        void SetVerticalAlignment(VerticalAlignment alignment);

    protected:
        void DrawSelf(NVGcontext* vg) override;

    private:
        const char* m_Text;
        HorizontalAlignment m_HorizontalAlignment = HorizontalAlignment::Left;
        VerticalAlignment m_VerticalAlignment = VerticalAlignment::Top;
    };
} // namespace Skoga