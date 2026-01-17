#include "Background.h"

#include <nanovg.h>

namespace Skoga
{
    BackgroundWidget::BackgroundWidget(const Color& color) : m_Color(color) {}

    void BackgroundWidget::SetColor(const Color& color)
    {
        m_Color = color;
    }

    void BackgroundWidget::DrawSelf(NVGcontext* vg)
    {
        nvgBeginPath(vg);
        nvgRect(vg, 0, 0, Width(), Height());
        nvgFillColor(vg, nvgRGBAf(m_Color.R, m_Color.G, m_Color.B, m_Color.A));
        nvgFill(vg);
    }
} // namespace Skoga