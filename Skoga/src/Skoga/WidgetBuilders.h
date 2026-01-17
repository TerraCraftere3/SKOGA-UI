#pragma once

#include "Skoga/Core.h"
#include "Skoga/Widget.h"
#include "Skoga/Widgets/Background.h"
#include "Skoga/Widgets/Container.h"
#include "Skoga/Widgets/Layout.h"
#include "Skoga/Widgets/Padding.h"
#include "Skoga/Widgets/Text.h"

#include <yoga/Yoga.h>

namespace Skoga
{
    // Helper function to add children to a widget
    template <typename... Children>
    inline void AddChildren(Ref<Widget> parent, Children... child)
    {
        // Fold expression to add all children
        (parent->AddChild(child), ...);
    }

    // Container builder
    template <typename... Children>
    inline Ref<ContainerWidget> Container(Children... child)
    {
        auto container = CreateRef<ContainerWidget>();
        YGNodeStyleSetFlexGrow(container->GetLayoutNode(), 1.0f);
        AddChildren(container, child...);
        return container;
    }

    // Stack (Layout) builder
    template <typename... Children>
    inline Ref<LayoutWidget> Stack(LayoutDirection direction, Children... child)
    {
        auto stack = CreateRef<LayoutWidget>(direction);
        YGNodeStyleSetFlexGrow(stack->GetLayoutNode(), 1.0f);
        AddChildren(stack, child...);
        return stack;
    }

    // Background builder
    template <typename... Children>
    inline Ref<BackgroundWidget> Background(float r, float g, float b, float a, Children... child)
    {
        auto background = CreateRef<BackgroundWidget>(r, g, b, a);
        YGNodeStyleSetFlexGrow(background->GetLayoutNode(), 1.0f);
        AddChildren(background, child...);
        return background;
    }

    // Text builder
    inline Ref<TextWidget> Text(const char* text, float fontSize = 16.0f,
                                HorizontalAlignment hAlign = HorizontalAlignment::Left,
                                VerticalAlignment vAlign = VerticalAlignment::Top)
    {
        auto textWidget = CreateRef<TextWidget>(text, fontSize);
        textWidget->SetHorizontalAlignment(hAlign);
        textWidget->SetVerticalAlignment(vAlign);
        YGNodeStyleSetFlexGrow(textWidget->GetLayoutNode(), 1.0f);
        return textWidget;
    }

    inline Ref<TextWidget> Text(const char* text, float fontSize = 16.0f, const char* fontName = FontSegoeui,
                                HorizontalAlignment hAlign = HorizontalAlignment::Left,
                                VerticalAlignment vAlign = VerticalAlignment::Top)
    {
        auto textWidget = CreateRef<TextWidget>(text, fontSize, fontName);
        textWidget->SetHorizontalAlignment(hAlign);
        textWidget->SetVerticalAlignment(vAlign);
        YGNodeStyleSetFlexGrow(textWidget->GetLayoutNode(), 1.0f);
        return textWidget;
    }

    // Padding builder
    template <typename... Children>
    inline Ref<PaddingWidget> Padding(float top, float right, float bottom, float left, Children... child)
    {
        auto padding = CreateRef<PaddingWidget>(top, right, bottom, left);
        YGNodeStyleSetFlexGrow(padding->GetLayoutNode(), 1.0f);
        AddChildren(padding, child...);
        return padding;
    }

    template <typename... Children>
    inline Ref<PaddingWidget> Padding(float paddingValue, Children... child)
    {
        return Padding(paddingValue, paddingValue, paddingValue, paddingValue, child...);
    }
} // namespace Skoga
