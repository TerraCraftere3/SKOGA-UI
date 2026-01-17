#include "Background.h"

#include <nanovg.h>

namespace Skoga
{
    BackgroundWidget::BackgroundWidget(float r, float g, float b, float a) : m_R(r), m_G(g), m_B(b), m_A(a) {}

    void BackgroundWidget::SetColor(float r, float g, float b, float a)
    {
        m_R = r;
        m_G = g;
        m_B = b;
        m_A = a;
    }

    void BackgroundWidget::DrawSelf(NVGcontext* vg)
    {
        nvgBeginPath(vg);
        nvgRect(vg, 0, 0, Width(), Height());
        nvgFillColor(vg, nvgRGBAf(m_R, m_G, m_B, m_A));
        nvgFill(vg);
    }
} // namespace Skoga