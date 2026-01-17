#pragma once

#include "Skoga/Widget.h"

namespace Skoga
{
    class BackgroundWidget : public Widget
    {
    public:
        BackgroundWidget(float r, float g, float b, float a);

        void SetColor(float r, float g, float b, float a);

    protected:
        void DrawSelf(NVGcontext* vg) override;

    private:
        float m_R, m_G, m_B, m_A;
    };
} // namespace Skoga