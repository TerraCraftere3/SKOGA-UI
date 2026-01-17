#pragma once

#include "Skoga/Color.h"
#include "Skoga/Widget.h"

namespace Skoga
{
    class BackgroundWidget : public Widget
    {
    public:
        BackgroundWidget(const Color& color);

        void SetColor(const Color& color);
        void SetCornerRadius(float radius);

    protected:
        void DrawSelf(NVGcontext* vg) override;

    private:
        Color m_Color;
        float m_CornerRadius = 0.0f;
    };
} // namespace Skoga