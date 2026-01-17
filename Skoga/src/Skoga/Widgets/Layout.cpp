#include "Layout.h"

namespace Skoga{
    LayoutWidget::LayoutWidget(LayoutDirection direction)
        : Widget()
    {
        SetDirection(direction);
    }

    void LayoutWidget::SetDirection(LayoutDirection direction)
    {
        if (direction == Row)
        {
            YGNodeStyleSetFlexDirection(GetLayoutNode(), YGFlexDirectionRow);
        }
        else // Column
        {
            YGNodeStyleSetFlexDirection(GetLayoutNode(), YGFlexDirectionColumn);
        }
    }

    void LayoutWidget::DrawSelf(NVGcontext* vg)
    {
    }
}