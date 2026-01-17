#ifdef SKOGA_DEBUG
#include "DebugSidebar.h"
#include "Application.h"
#include "WidgetBuilders.h"

#include <nanovg.h>
#include <string>

namespace Skoga
{
    const float DebugSidebar::SIDEBAR_WIDTH = 350.0f;
    const float DebugSidebar::PADDING = 12.0f;

    DebugSidebar::DebugSidebar()
    {
        YGNodeStyleSetWidth(GetLayoutNode(), SIDEBAR_WIDTH);
        YGNodeStyleSetFlexDirection(GetLayoutNode(), YGFlexDirectionRow);
        YGNodeStyleSetFlexGrow(GetLayoutNode(), 0.0f);
        YGNodeStyleSetAlignItems(GetLayoutNode(), YGAlignFlexStart);

        Update();
    }

    void DebugSidebar::Update()
    {
        // clang-format off
        ClearChildren();
        AddChild(Container(
            Background(Gray_800,
                Padding(PADDING,
                    Text("Debug Tools")
                        .FontSize(16.0f)
                        .Color(White)
                        .Font(FontConsolas)
                        .HAlign(HorizontalAlignment::Center)
                        .VAlign(VerticalAlignment::Middle)
                )
            )
        ));
        // clang-format on
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
    }
} // namespace Skoga
#endif