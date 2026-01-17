#include "Widget.h"

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
        DrawSelf(vg);

        for (auto& child : m_Children)
            child->Draw(vg);
    }

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

} // namespace Skoga