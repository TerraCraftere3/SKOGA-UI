#include "Text.h"
#include "Skoga/Stylesheet.h"

#include <nanovg.h>

namespace Skoga
{
    TextWidget::TextWidget(const char* text) : m_Text(text)
    {
        // Set default font size if not specified in style
        if (!GetStyle().FontSize.has_value())
        {
            GetStyle().FontSize = 16.0f;
        }

        // Set default text color if not specified
        if (!GetStyle().TextColor.has_value())
        {
            GetStyle().TextColor = Gray_100;
        }

        // Set default font if not specified
        if (!GetStyle().FontFamily.has_value())
        {
            GetStyle().FontFamily = FontSegoeui;
        }

        // Set minimum size for the text widget
        float fontSize = GetStyle().FontSize.value_or(16.0f);
        YGNodeStyleSetMinHeight(GetLayoutNode(), fontSize * 1.5f);
        YGNodeStyleSetMinWidth(GetLayoutNode(), 50.0f);
    }

    void TextWidget::SetText(const char* text)
    {
        m_Text = text;
    }

    void TextWidget::SetHorizontalAlignment(HorizontalAlignment alignment)
    {
        m_HorizontalAlignment = alignment;
    }

    void TextWidget::SetVerticalAlignment(VerticalAlignment alignment)
    {
        m_VerticalAlignment = alignment;
    }

    void TextWidget::DrawSelf(NVGcontext* vg)
    {
        const auto& style = GetStyle();

        float fontSize = style.FontSize.value_or(16.0f);
        const char* fontName = style.FontFamily.value_or(FontSegoeui);
        Color textColor = style.TextColor.value_or(Color(0.9f, 0.9f, 0.9f));

        nvgFontSize(vg, fontSize);
        nvgFontFace(vg, fontName);
        nvgFillColor(vg, nvgRGBAf(textColor.R, textColor.G, textColor.B, textColor.A));

        // Convert alignment enums to NanoVG flags
        int hAlign = NVG_ALIGN_LEFT;
        switch (m_HorizontalAlignment)
        {
            case HorizontalAlignment::Left:
                hAlign = NVG_ALIGN_LEFT;
                break;
            case HorizontalAlignment::Center:
                hAlign = NVG_ALIGN_CENTER;
                break;
            case HorizontalAlignment::Right:
                hAlign = NVG_ALIGN_RIGHT;
                break;
        }

        int vAlign = NVG_ALIGN_TOP;
        switch (m_VerticalAlignment)
        {
            case VerticalAlignment::Top:
                vAlign = NVG_ALIGN_TOP;
                break;
            case VerticalAlignment::Middle:
                vAlign = NVG_ALIGN_MIDDLE;
                break;
            case VerticalAlignment::Bottom:
                vAlign = NVG_ALIGN_BOTTOM;
                break;
        }

        nvgTextAlign(vg, hAlign | vAlign);

        // Calculate position based on alignment
        float x = 0.0f;
        float y = 0.0f;
        float width = YGNodeLayoutGetWidth(GetLayoutNode());
        float height = YGNodeLayoutGetHeight(GetLayoutNode());

        if (m_HorizontalAlignment == HorizontalAlignment::Center)
        {
            x = width * 0.5f;
        }
        else if (m_HorizontalAlignment == HorizontalAlignment::Right)
        {
            x = width;
        }

        if (m_VerticalAlignment == VerticalAlignment::Middle)
        {
            y = height * 0.5f;
        }
        else if (m_VerticalAlignment == VerticalAlignment::Bottom)
        {
            y = height;
        }

        nvgText(vg, x, y, m_Text, nullptr);
    }
} // namespace Skoga