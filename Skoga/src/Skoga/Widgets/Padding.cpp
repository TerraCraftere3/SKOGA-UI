#include "Padding.h"

namespace Skoga
{
    PaddingWidget::PaddingWidget(float top, float right, float bottom, float left)
        : m_Top(top), m_Right(right), m_Bottom(bottom), m_Left(left)
    {
        SetPadding(top, right, bottom, left);
    }

    void PaddingWidget::SetPadding(float top, float right, float bottom, float left)
    {
        m_Top = top;
        m_Right = right;
        m_Bottom = bottom;
        m_Left = left;

        YGNodeStyleSetPadding(GetLayoutNode(), YGEdgeTop, top);
        YGNodeStyleSetPadding(GetLayoutNode(), YGEdgeRight, right);
        YGNodeStyleSetPadding(GetLayoutNode(), YGEdgeBottom, bottom);
        YGNodeStyleSetPadding(GetLayoutNode(), YGEdgeLeft, left);
    }

    void PaddingWidget::DrawSelf(NVGcontext* vg) {}
} // namespace Skoga