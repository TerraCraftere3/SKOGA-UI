#pragma once

#include "Skoga/Core.h"
#include "Skoga/Widget.h"
#include "Skoga/Widgets/Container.h"
#include "Skoga/Widgets/Layout.h"
#include "Skoga/Widgets/Background.h"

#include <yoga/Yoga.h>

namespace Skoga
{
    // Helper function to add children to a widget
    template<typename... Children>
    inline void AddChildren(Ref<Widget> parent, Children... children)
    {
        // Fold expression to add all children
        (parent->AddChild(children), ...);
    }

    // Container builder
    template<typename... Children>
    inline Ref<ContainerWidget> Container(Children... children)
    {
        auto container = CreateRef<ContainerWidget>();
        YGNodeStyleSetFlexGrow(container->GetLayoutNode(), 1.0f);
        AddChildren(container, children...);
        return container;
    }

    // Stack (Layout) builder
    template<typename... Children>
    inline Ref<LayoutWidget> Stack(LayoutDirection direction, Children... children)
    {
        auto stack = CreateRef<LayoutWidget>(direction);
        YGNodeStyleSetFlexGrow(stack->GetLayoutNode(), 1.0f);
        AddChildren(stack, children...);
        return stack;
    }

    // Background builder
    template<typename... Children>
    inline Ref<BackgroundWidget> Background(float r, float g, float b, float a, Children... children)
    {
        auto background = CreateRef<BackgroundWidget>(r, g, b, a);
        YGNodeStyleSetFlexGrow(background->GetLayoutNode(), 1.0f);
        AddChildren(background, children...);
        return background;
    }

} // namespace Skoga
