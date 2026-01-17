#pragma once

#include "Skoga/Widget.h"

namespace Skoga
{
    enum LayoutDirection
    {
        Row,
        Column
    };

    class LayoutWidget : public Widget
    {
    public:
        LayoutWidget(LayoutDirection direction);

        void SetDirection(LayoutDirection direction);

    protected:
        void DrawSelf(NVGcontext* vg) override;
    };
} // namespace Skoga