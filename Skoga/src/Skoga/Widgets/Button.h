#pragma once

#include "Skoga/Color.h"
#include "Skoga/Widget.h"

namespace Skoga
{
    class ButtonWidget : public Widget
    {
    public:
        ButtonWidget(const Color& backgroundColor);

        void SetBackgroundColor(const Color& color);
        void SetHoverColor(const Color& color);
        void SetPadding(float padding);
        void SetPadding(float top, float right, float bottom, float left);
        void SetCornerRadius(float radius);

    protected:
        void DrawSelf(NVGcontext* vg) override;

    private:
        Color m_BackgroundColor;
        Color m_HoverColor;
        float m_PaddingTop = 8.0f;
        float m_PaddingRight = 12.0f;
        float m_PaddingBottom = 8.0f;
        float m_PaddingLeft = 12.0f;
        float m_CornerRadius = 4.0f;
        bool m_IsHovering = false;

        friend class Widget;
    };
} // namespace Skoga
