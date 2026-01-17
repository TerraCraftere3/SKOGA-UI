#include "Background.h"

#include <nanovg.h>

namespace Skoga
{
    BackgroundWidget::BackgroundWidget(const Color& color) : m_Color(color) {}

    void BackgroundWidget::SetColor(const Color& color)
    {
        m_Color = color;
    }

    void BackgroundWidget::SetCornerRadius(float radius)
    {
        m_CornerRadius = radius;
    }

    void BackgroundWidget::DrawSelf(NVGcontext* vg)
    {
        nvgBeginPath(vg);
        if (m_CornerRadius > 0.0f)
            nvgRoundedRect(vg, 0, 0, Width(), Height(), m_CornerRadius);
        else
            nvgRect(vg, 0, 0, Width(), Height());
        nvgFillColor(vg, nvgRGBAf(m_Color.R, m_Color.G, m_Color.B, m_Color.A));
        nvgFill(vg);
    }
} // namespace Skoga