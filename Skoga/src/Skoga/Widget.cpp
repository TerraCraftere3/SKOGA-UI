#include "Widget.h"
#include <nanovg.h>
#include "Skoga/Color.h"

namespace Skoga
{

    Widget::Widget()
    {
        m_LayoutNode = YGNodeNew();
        YGNodeSetContext(m_LayoutNode, this);
    }

    Widget::~Widget()
    {
        YGNodeFree(m_LayoutNode);
    }

    void Widget::ClearChildren()
    {
        for (auto& child : m_Children)
        {
            child->m_Parent = nullptr;
            YGNodeRemoveChild(m_LayoutNode, child->m_LayoutNode);
        }
        m_Children.clear();
    }

    void Widget::AddChild(Ref<Widget> child)
    {
        child->m_Parent = this;

        YGNodeInsertChild(m_LayoutNode, child->m_LayoutNode, YGNodeGetChildCount(m_LayoutNode));

        m_Children.emplace_back(std::move(child));
    }

    const std::vector<Ref<Widget>>& Widget::GetChildren() const
    {
        return m_Children;
    }

    Widget* Widget::GetParent() const
    {
        return m_Parent;
    }

    YGNodeRef Widget::GetLayoutNode() const
    {
        return m_LayoutNode;
    }

    void Widget::OnLayout()
    {
        for (auto& child : m_Children)
            child->OnLayout();
    }

    void Widget::Draw(NVGcontext* vg)
    {
        nvgSave(vg);
        nvgTranslate(vg, X(), Y());

        DrawSelf(vg);

        for (auto& child : m_Children)
            child->Draw(vg);

        nvgRestore(vg);
    }

#ifdef SKOGA_DEBUG
    void Widget::DrawDebug(NVGcontext* vg)
    {
        nvgSave(vg);
        nvgTranslate(vg, X(), Y());

        // Compute depth in the widget tree
        int depth = 0;
        const Widget* p = GetParent();
        while (p)
        {
            ++depth;
            p = p->GetParent();
        }

        // Map depth to a wavelength and color
        float wavelength = 780.0f - (depth % 10) * 40.0f; // cycles through visible spectrum
        Color c = WavelengthToColor(wavelength);

        nvgBeginPath(vg);
        nvgRect(vg, 0, 0, Width(), Height());
        nvgStrokeColor(vg, nvgRGBAf(c.R, c.G, c.B, 0.5f));
        nvgStroke(vg);

        DrawSelf(vg);

        for (auto& child : m_Children)
            child->DrawDebug(vg);

        nvgRestore(vg);
    }
#endif

    float Widget::X() const
    {
        return YGNodeLayoutGetLeft(m_LayoutNode);
    }

    float Widget::Y() const
    {
        return YGNodeLayoutGetTop(m_LayoutNode);
    }

    float Widget::Width() const
    {
        return YGNodeLayoutGetWidth(m_LayoutNode);
    }

    float Widget::Height() const
    {
        return YGNodeLayoutGetHeight(m_LayoutNode);
    }

    void Widget::SetOnClick(OnClickCallback callback)
    {
        m_OnClick = callback;
    }

    void Widget::SetOnHover(OnHoverCallback callback)
    {
        m_OnHover = callback;
    }

    void Widget::TriggerClick()
    {
        if (m_OnClick)
        {
            m_OnClick();
        }
    }

    void Widget::TriggerHover(bool isHovering)
    {
        if (m_OnHover)
        {
            m_OnHover(isHovering);
        }
    }

    Widget* Widget::HitTest(float x, float y)
    {
        // Check if point is inside this widget
        if (!IsPointInside(x, y))
        {
            return nullptr;
        }

        // Check children from last to first (top-most drawn first)
        for (auto it = m_Children.rbegin(); it != m_Children.rend(); ++it)
        {
            float childX = x - (*it)->X();
            float childY = y - (*it)->Y();
            Widget* hit = (*it)->HitTest(childX, childY);
            if (hit)
            {
                return hit;
            }
        }

        // No children were hit, return this widget
        return this;
    }

    bool Widget::IsPointInside(float x, float y) const
    {
        float w = Width();
        float h = Height();
        return x >= 0 && x <= w && y >= 0 && y <= h;
    }

    Style& Widget::GetStyle()
    {
        return m_Style;
    }

    const Style& Widget::GetStyle() const
    {
        return m_Style;
    }

    void Widget::ApplyStyle()
    {
        Skoga::ApplyStyle(m_LayoutNode, m_Style);
    }

} // namespace Skoga