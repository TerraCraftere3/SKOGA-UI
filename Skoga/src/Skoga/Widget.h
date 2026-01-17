#pragma once

#include "Skoga/Core.h"

#include <yoga/Yoga.h>
#include <memory>
#include <vector>

struct NVGcontext;

namespace Skoga
{

    class Widget
    {
    public:
        Widget();
        virtual ~Widget();

        // Non-copyable (layout trees should not be copied)
        Widget(const Widget&) = delete;
        Widget& operator=(const Widget&) = delete;

        // Hierarchy
        void AddChild(Ref<Widget> child);
        const std::vector<Ref<Widget>>& GetChildren() const;

        Widget* GetParent() const;

        // Layout
        YGNodeRef GetLayoutNode() const;

        // Called after Yoga layout calculation
        virtual void OnLayout();

        // Rendering entry point
        void Draw(NVGcontext* vg);

    protected:
        // Override this to draw the widget itself
        virtual void DrawSelf(NVGcontext* vg) = 0;

        // Layout helpers
        float X() const;
        float Y() const;
        float Width() const;
        float Height() const;

    private:
        Widget* m_Parent = nullptr;
        std::vector<Ref<Widget>> m_Children;

        YGNodeRef m_LayoutNode = nullptr;
    };

} // namespace Skoga