#include "DebugSidebar.h"

#include <nanovg.h>

namespace Skoga
{
    const float DebugSidebar::SIDEBAR_WIDTH = 250.0f;
    const float DebugSidebar::TOGGLE_HEIGHT = 32.0f;
    const float DebugSidebar::PADDING = 12.0f;
    const float DebugSidebar::ITEM_SPACING = 8.0f;

    DebugSidebar::DebugSidebar()
    {
        YGNodeStyleSetWidth(GetLayoutNode(), SIDEBAR_WIDTH);
        YGNodeStyleSetFlexDirection(GetLayoutNode(), YGFlexDirectionColumn);
        YGNodeStyleSetFlexGrow(GetLayoutNode(), 0.0f);
    }

    void DebugSidebar::DrawSelf(NVGcontext* vg)
    {
        float w = Width();
        float h = Height();

        // Draw sidebar background
        nvgBeginPath(vg);
        nvgRect(vg, 0, 0, w, h);
        nvgFillColor(vg, nvgRGBAf(0.12f, 0.12f, 0.14f, 1.0f));
        nvgFill(vg);

        // Draw left border
        nvgBeginPath(vg);
        nvgRect(vg, 0, 0, 1, h);
        nvgFillColor(vg, nvgRGBAf(0.3f, 0.3f, 0.3f, 1.0f));
        nvgFill(vg);

        // Draw title
        nvgFontSize(vg, 14.0f);
        nvgFontFace(vg, "consolas");
        nvgFillColor(vg, nvgRGBAf(0.9f, 0.9f, 0.9f, 1.0f));
        nvgText(vg, PADDING, PADDING + 4, "Debug Tools", NULL);
    }

    void DebugSidebar::HandleClick(float relativeX, float relativeY)
    {
    }
} // namespace Skoga
