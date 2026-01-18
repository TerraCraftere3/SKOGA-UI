#include "Button.h"
#include "Skoga/Stylesheet.h"

#include <nanovg.h>

namespace Skoga
{
    ButtonWidget::ButtonWidget()
    {
        // Button only takes the space it needs (no flex grow)
        YGNodeStyleSetFlexGrow(GetLayoutNode(), 0.0f);

        // Set default padding on layout node
        YGNodeStyleSetPadding(GetLayoutNode(), YGEdgeTop, 8.0f);
        YGNodeStyleSetPadding(GetLayoutNode(), YGEdgeRight, 12.0f);
        YGNodeStyleSetPadding(GetLayoutNode(), YGEdgeBottom, 8.0f);
        YGNodeStyleSetPadding(GetLayoutNode(), YGEdgeLeft, 12.0f);

        // Set flex direction to wrap children
        YGNodeStyleSetFlexDirection(GetLayoutNode(), YGFlexDirectionRow);
        YGNodeStyleSetAlignItems(GetLayoutNode(), YGAlignCenter);
        YGNodeStyleSetJustifyContent(GetLayoutNode(), YGJustifyCenter);

        // Set minimum size
        YGNodeStyleSetMinWidth(GetLayoutNode(), 60.0f);
        YGNodeStyleSetMinHeight(GetLayoutNode(), 32.0f);

        // Set default button color if not specified in style
        if (!GetStyle().BackgroundColor.has_value())
        {
            GetStyle().BackgroundColor = Color(0.4f, 0.6f, 0.95f);
        }

        // Set up hover callback
        SetOnHover([this](bool hovering) { m_IsHovering = hovering; });
    }

    void ButtonWidget::DrawSelf(NVGcontext* vg)
    {
        const auto& style = GetStyle();

        // Get button color
        Color bgColor = style.BackgroundColor.value_or(Color(0.4f, 0.6f, 0.95f));

        // Generate hover color if not specified
        Color displayColor;
        if (m_IsHovering)
        {
            displayColor = Color(bgColor.R * 0.85f, bgColor.G * 0.85f, bgColor.B * 0.85f, bgColor.A);
        }
        else
        {
            displayColor = bgColor;
        }

        float w = Width();
        float h = Height();
        float radius = style.BorderRadius.value_or(4.0f);

        // Draw rounded rectangle at origin (0, 0) due to translation in Widget::Draw
        nvgBeginPath(vg);
        nvgRoundedRect(vg, 0, 0, w, h, radius);
        nvgFillColor(vg, nvgRGBA(static_cast<unsigned char>(displayColor.R * 255),
                                 static_cast<unsigned char>(displayColor.G * 255),
                                 static_cast<unsigned char>(displayColor.B * 255),
                                 static_cast<unsigned char>(displayColor.A * 255)));
        nvgFill(vg);
    }
} // namespace Skoga