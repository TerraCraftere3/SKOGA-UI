#pragma once

#ifdef SKOGA_DEBUG
#include "Skoga/Color.h"
#include "Skoga/Core.h"
#include "Skoga/Widget.h"

namespace Skoga
{
    class DebugSidebar : public Widget
    {
    public:
        DebugSidebar();

        void Update();

    protected:
        void DrawSelf(NVGcontext* vg) override;

    private:
        static const float SIDEBAR_WIDTH;
        static const float PADDING;
    };
} // namespace Skoga
#endif