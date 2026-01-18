#pragma once

#include "Skoga/Color.h"
#include "Skoga/Widget.h"

namespace Skoga
{
    class ButtonWidget : public Widget
    {
    public:
        ButtonWidget();

    protected:
        void DrawSelf(NVGcontext* vg) override;

    private:
        bool m_IsHovering = false;

        friend class Widget;
    };
} // namespace Skoga
