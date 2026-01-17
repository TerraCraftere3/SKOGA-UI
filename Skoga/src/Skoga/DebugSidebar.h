#pragma once

#include "Skoga/Core.h"
#include "Skoga/Widget.h"
#include "Skoga/Color.h"

namespace Skoga
{
    class DebugSidebar : public Widget
    {
    public:
        DebugSidebar();

        void HandleClick(float relativeX, float relativeY);

    protected:
        void DrawSelf(NVGcontext* vg) override;

    private:
        static const float SIDEBAR_WIDTH;
        static const float TOGGLE_HEIGHT;
        static const float PADDING;
        static const float ITEM_SPACING;
    };
} // namespace Skoga
