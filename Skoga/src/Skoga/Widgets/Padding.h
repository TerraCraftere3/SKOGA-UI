#pragma once

#include "Skoga/Widget.h"

namespace Skoga
{
    class PaddingWidget : public Widget
    {
    public:
        PaddingWidget(float top, float right, float bottom, float left);

        void SetPadding(float top, float right, float bottom, float left);

    protected:
        void DrawSelf(NVGcontext* vg) override;

    private:
        float m_Top, m_Right, m_Bottom, m_Left;
    };
} // namespace Skoga