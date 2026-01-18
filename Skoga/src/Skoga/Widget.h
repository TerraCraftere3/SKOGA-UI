#pragma once

#include "Skoga/Core.h"
#include "Skoga/Stylesheet.h"

#include <yoga/Yoga.h>
#include <functional>
#include <memory>
#include <vector>

struct NVGcontext;

namespace Skoga
{

    class Widget
    {
    public:
        using OnClickCallback = std::function<void()>;
        using OnHoverCallback = std::function<void(bool)>;

        Widget();
        virtual ~Widget();

        // Non-copyable (layout trees should not be copied)
        Widget(const Widget&) = delete;
        Widget& operator=(const Widget&) = delete;

        // Hierarchy
        void ClearChildren();
        void AddChild(Ref<Widget> child);
        const std::vector<Ref<Widget>>& GetChildren() const;

        Widget* GetParent() const;

        // Layout
        YGNodeRef GetLayoutNode() const;

        // Called after Yoga layout calculation
        virtual void OnLayout();

        // Rendering entry point
        void Draw(NVGcontext* vg);
#ifdef SKOGA_DEBUG
        void DrawDebug(NVGcontext* vg);
#endif

        // Event handlers
        void SetOnClick(OnClickCallback callback);
        void SetOnHover(OnHoverCallback callback);
        void TriggerClick();
        void TriggerHover(bool isHovering);

        // Hit testing - returns the deepest widget at the given position
        Widget* HitTest(float x, float y);

        // Check if point is inside this widget's bounds
        bool IsPointInside(float x, float y) const;

        // Layout accessors
        float X() const;
        float Y() const;
        float Width() const;
        float Height() const;

        // Styling
        Style& GetStyle();
        const Style& GetStyle() const;
        void ApplyStyle();

    protected:
        // Override this to draw the widget itself
        virtual void DrawSelf(NVGcontext* vg) = 0;

    private:
        Widget* m_Parent = nullptr;
        std::vector<Ref<Widget>> m_Children;

        YGNodeRef m_LayoutNode = nullptr;
        OnClickCallback m_OnClick;
        OnHoverCallback m_OnHover;
        Style m_Style;
    };

} // namespace Skoga