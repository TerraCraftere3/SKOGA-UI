#include "Button.h"

#include <nanovg.h>

namespace Skoga
{
    ButtonWidget::ButtonWidget(const Color& backgroundColor) : m_BackgroundColor(backgroundColor)
    {
        m_HoverColor = Color(m_BackgroundColor.R * 0.85f, m_BackgroundColor.G * 0.85f, m_BackgroundColor.B * 0.85f,
                             m_BackgroundColor.A);

        // Button only takes the space it needs (no flex grow)
        YGNodeStyleSetFlexGrow(GetLayoutNode(), 0.0f);

        // Set default padding on layout node
        YGNodeStyleSetPadding(GetLayoutNode(), YGEdgeTop, m_PaddingTop);
        YGNodeStyleSetPadding(GetLayoutNode(), YGEdgeRight, m_PaddingRight);
        YGNodeStyleSetPadding(GetLayoutNode(), YGEdgeBottom, m_PaddingBottom);
        YGNodeStyleSetPadding(GetLayoutNode(), YGEdgeLeft, m_PaddingLeft);

        // Set flex direction to wrap children
        YGNodeStyleSetFlexDirection(GetLayoutNode(), YGFlexDirectionRow);
        YGNodeStyleSetAlignItems(GetLayoutNode(), YGAlignCenter);
        YGNodeStyleSetJustifyContent(GetLayoutNode(), YGJustifyCenter);

        // Set minimum size
        YGNodeStyleSetMinWidth(GetLayoutNode(), 60.0f);
        YGNodeStyleSetMinHeight(GetLayoutNode(), 32.0f);

        // Set up hover callback
        SetOnHover([this](bool hovering) { m_IsHovering = hovering; });
    }

    void ButtonWidget::SetBackgroundColor(const Color& color)
    {
        m_BackgroundColor = color;
    }

    void ButtonWidget::SetHoverColor(const Color& color)
    {
        m_HoverColor = color;
    }

    void ButtonWidget::SetPadding(float padding)
    {
        SetPadding(padding, padding, padding, padding);
    }

    void ButtonWidget::SetPadding(float top, float right, float bottom, float left)
    {
        m_PaddingTop = top;
        m_PaddingRight = right;
        m_PaddingBottom = bottom;
        m_PaddingLeft = left;

        // Update layout node padding
        YGNodeStyleSetPadding(GetLayoutNode(), YGEdgeTop, top);
        YGNodeStyleSetPadding(GetLayoutNode(), YGEdgeRight, right);
        YGNodeStyleSetPadding(GetLayoutNode(), YGEdgeBottom, bottom);
        YGNodeStyleSetPadding(GetLayoutNode(), YGEdgeLeft, left);
    }

    void ButtonWidget::SetCornerRadius(float radius)
    {
        m_CornerRadius = radius;
    }

    void ButtonWidget::DrawSelf(NVGcontext* vg)
    {
        // Use relative coordinates since Widget::Draw already translates
        float w = Width();
        float h = Height();

        // Choose color based on hover state
        const Color& drawColor = m_IsHovering ? m_HoverColor : m_BackgroundColor;

        // Draw rounded rectangle at origin (0, 0) due to translation in Widget::Draw
        nvgBeginPath(vg);
        nvgRoundedRect(vg, 0, 0, w, h, m_CornerRadius);
        nvgFillColor(
            vg, nvgRGBA(static_cast<unsigned char>(drawColor.R * 255), static_cast<unsigned char>(drawColor.G * 255),
                        static_cast<unsigned char>(drawColor.B * 255), static_cast<unsigned char>(drawColor.A * 255)));
        nvgFill(vg);
    }
} // namespace Skoga
