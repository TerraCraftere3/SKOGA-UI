#include "Text.h"

#include <nanovg.h>

namespace Skoga
{
    TextWidget::TextWidget(const char* text, float fontSize)
        : m_Text(text), m_FontSize(fontSize)
    {
        // Set minimum size for the text widget
        YGNodeStyleSetHeight(GetLayoutNode(), fontSize * 1.5f);
        YGNodeStyleSetMinWidth(GetLayoutNode(), 50.0f);
    }

    void TextWidget::SetText(const char* text)
    {
        m_Text = text;
    }

    void TextWidget::SetFontSize(float fontSize)
    {
        m_FontSize = fontSize;
        YGNodeStyleSetHeight(GetLayoutNode(), fontSize * 1.5f);
    }

    void TextWidget::DrawSelf(NVGcontext* vg)
    {
        nvgFontSize(vg, m_FontSize);
        nvgFontFace(vg, "sans");
        nvgFillColor(vg, nvgRGBA(255, 255, 255, 255));
        nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
        nvgText(vg, 0, 0, m_Text, nullptr);
    }
} // namespace Skoga