#include "DebugOverlay.h"
#include "DebugSidebar.h"

#include "Skoga/WidgetBuilders.h"

namespace Skoga
{
    Ref<Widget> CreateDebugOverlay(Ref<DebugSidebar> debugSidebar)
    {
        // clang-format off
        return Container(
            Background(Gray_900,
                Padding(10.0f,
                    TextBuilder("Debug Panel - Press F6 to toggle, use sidebar to customize")
                        .FontSize(12.0f)
                        .Color(Blue_300)
                        .Font(FontConsolas)
                        .HAlign(HorizontalAlignment::Left)
                        .VAlign(VerticalAlignment::Top)
                )
            )
        );
        // clang-format on
    }
}