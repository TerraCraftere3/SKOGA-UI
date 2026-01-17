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

    protected:
        void DrawSelf(NVGcontext* vg) override;

    private:
        Color m_Color;
    };
} // namespace Skoga