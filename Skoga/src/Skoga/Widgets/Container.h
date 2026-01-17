#pragma once

#include "Skoga/Widget.h"

namespace Skoga
{
    class ContainerWidget : public Widget
    {
    public:
        ContainerWidget();

    protected:
        void DrawSelf(NVGcontext* vg) override;
    };
} // namespace Skoga