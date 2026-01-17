#include "Text.h"

#include <nanovg.h>

namespace Skoga
{
    TextWidget::TextWidget(const char* text, float fontSize, const char* fontName)
        : m_Text(text), m_FontSize(fontSize), m_FontName(fontName)
    {
        // Set minimum size for the text widget
        YGNodeStyleSetMinHeight(GetLayoutNode(), fontSize * 1.5f);
        YGNodeStyleSetMinWidth(GetLayoutNode(), 50.0f);
    }

    void TextWidget::SetText(const char* text)
    {
        m_Text = text;
    }

    void TextWidget::SetFontSize(float fontSize)
    {
        m_FontSize = fontSize;
        YGNodeStyleSetMinHeight(GetLayoutNode(), fontSize * 1.5f);
    }

    void TextWidget::SetFontName(const char* fontName)
    {
        m_FontName = fontName;
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
        nvgFontSize(vg, m_FontSize);
        nvgFontFace(vg, m_FontName);
        nvgFillColor(vg, nvgRGBA(255, 255, 255, 255));

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