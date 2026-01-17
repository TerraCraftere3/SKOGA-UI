#pragma once

#include "Skoga/Core.h"
#include "Skoga/Widget.h"
#include "Skoga/Widgets/Background.h"
#include "Skoga/Widgets/Button.h"
#include "Skoga/Widgets/Container.h"
#include "Skoga/Widgets/Layout.h"
#include "Skoga/Widgets/Padding.h"
#include "Skoga/Widgets/Text.h"

#include <yoga/Yoga.h>

namespace Skoga
{
    // Helper to convert builder types to widget refs
    template <typename T>
    inline auto ToWidget(T&& val) -> decltype(Ref<Widget>(val.Build()))
    {
        return Ref<Widget>(val.Build());
    }

    template <typename T>
    inline Ref<Widget> ToWidget(Ref<T> val)
    {
        return val;
    }

    // Helper function to add children to a widget
    template <typename... Children>
    inline void AddChildren(Ref<Widget> parent, Children&&... child)
    {
        (parent->AddChild(ToWidget(std::forward<Children>(child))), ...);
    }

    // ========== Text ==========
    class Text
    {
    private:
        const char* m_Text;
        float m_FontSize = 16.0f;
        Color m_Color = Gray_100;
        const char* m_FontName = FontSegoeui;
        HorizontalAlignment m_HAlign = HorizontalAlignment::Left;
        VerticalAlignment m_VAlign = VerticalAlignment::Top;

    public:
        explicit Text(const char* text) : m_Text(text) {}

        Text& FontSize(float size)
        {
            m_FontSize = size;
            return *this;
        }

        Text& Color(const Skoga::Color& color)
        {
            m_Color = color;
            return *this;
        }

        Text& Font(const char* fontName)
        {
            m_FontName = fontName;
            return *this;
        }

        Text& HAlign(HorizontalAlignment align)
        {
            m_HAlign = align;
            return *this;
        }

        Text& VAlign(VerticalAlignment align)
        {
            m_VAlign = align;
            return *this;
        }

        Text& Align(HorizontalAlignment hAlign, VerticalAlignment vAlign)
        {
            m_HAlign = hAlign;
            m_VAlign = vAlign;
            return *this;
        }

        Ref<TextWidget> Build()
        {
            auto textWidget = CreateRef<TextWidget>(m_Text, m_FontSize, m_Color, m_FontName);
            textWidget->SetHorizontalAlignment(m_HAlign);
            textWidget->SetVerticalAlignment(m_VAlign);
            YGNodeStyleSetFlexGrow(textWidget->GetLayoutNode(), 1.0f);
            return textWidget;
        }

        operator Ref<TextWidget>() { return Build(); }
    };

    // ========== Background ==========
    class Background
    {
    private:
        Color m_Color;
        float m_CornerRadius = 0.0f;
        std::vector<Ref<Widget>> m_Children;

    public:
        explicit Background(const Color& color) : m_Color(color) {}

        template <typename... Children>
        explicit Background(const Color& color, Children... child) : m_Color(color)
        {
            (m_Children.push_back(ToWidget(child)), ...);
        }

        Background& CornerRadius(float radius)
        {
            m_CornerRadius = radius;
            return *this;
        }

        template <typename... Children>
        Background& Add(Children... child)
        {
            (m_Children.push_back(ToWidget(child)), ...);
            return *this;
        }

        Ref<BackgroundWidget> Build()
        {
            auto background = CreateRef<BackgroundWidget>(m_Color);
            YGNodeStyleSetFlexGrow(background->GetLayoutNode(), 1.0f);
            for (auto& child : m_Children)
            {
                background->AddChild(child);
            }
            background->SetCornerRadius(m_CornerRadius);
            return background;
        }

        operator Ref<BackgroundWidget>() { return Build(); }
    };

    // ========== Button ==========
    class Button
    {
    private:
        Color m_Color;
        Color m_HoverColor;
        float m_CornerRadius = 4.0f;
        float m_PaddingTop = 8.0f;
        float m_PaddingRight = 12.0f;
        float m_PaddingBottom = 8.0f;
        float m_PaddingLeft = 12.0f;
        std::vector<Ref<Widget>> m_Children;
        Widget::OnClickCallback m_OnClick;

    public:
        explicit Button(const Color& color) : m_Color(color)
        {
            // Auto-generate hover color (darker)
            m_HoverColor = Color(color.R * 0.85f, color.G * 0.85f, color.B * 0.85f, color.A);
        }

        template <typename... Children>
        explicit Button(const Color& color, Children... child) : m_Color(color)
        {
            m_HoverColor = Color(color.R * 0.85f, color.G * 0.85f, color.B * 0.85f, color.A);
            (m_Children.push_back(ToWidget(child)), ...);
        }

        Button& HoverColor(const Color& color)
        {
            m_HoverColor = color;
            return *this;
        }

        Button& CornerRadius(float radius)
        {
            m_CornerRadius = radius;
            return *this;
        }

        Button& Padding(float value)
        {
            m_PaddingTop = m_PaddingRight = m_PaddingBottom = m_PaddingLeft = value;
            return *this;
        }

        Button& Padding(float top, float right, float bottom, float left)
        {
            m_PaddingTop = top;
            m_PaddingRight = right;
            m_PaddingBottom = bottom;
            m_PaddingLeft = left;
            return *this;
        }

        Button& OnClick(Widget::OnClickCallback callback)
        {
            m_OnClick = callback;
            return *this;
        }

        template <typename... Children>
        Button& Add(Children... child)
        {
            (m_Children.push_back(ToWidget(child)), ...);
            return *this;
        }

        Ref<ButtonWidget> Build()
        {
            auto button = CreateRef<ButtonWidget>(m_Color);
            button->SetHoverColor(m_HoverColor);
            button->SetPadding(m_PaddingTop, m_PaddingRight, m_PaddingBottom, m_PaddingLeft);
            button->SetCornerRadius(m_CornerRadius);
            if (m_OnClick)
            {
                button->SetOnClick(m_OnClick);
            }
            for (auto& child : m_Children)
            {
                button->AddChild(child);
            }
            return button;
        }

        operator Ref<ButtonWidget>() { return Build(); }
    };

    // ========== PaddingBuilder ==========
    class Padding
    {
    private:
        float m_Top;
        float m_Right;
        float m_Bottom;
        float m_Left;
        std::vector<Ref<Widget>> m_Children;

    public:
        explicit Padding(float value) : m_Top(value), m_Right(value), m_Bottom(value), m_Left(value) {}

        Padding(float top, float right, float bottom, float left)
            : m_Top(top), m_Right(right), m_Bottom(bottom), m_Left(left)
        {
        }

        template <typename... Children>
        explicit Padding(float value, Children... child) : m_Top(value), m_Right(value), m_Bottom(value), m_Left(value)
        {
            (m_Children.push_back(ToWidget(child)), ...);
        }

        template <typename... Children>
        Padding(float top, float right, float bottom, float left, Children... child)
            : m_Top(top), m_Right(right), m_Bottom(bottom), m_Left(left)
        {
            (m_Children.push_back(ToWidget(child)), ...);
        }

        Padding& Top(float value)
        {
            m_Top = value;
            return *this;
        }

        Padding& Right(float value)
        {
            m_Right = value;
            return *this;
        }

        Padding& Bottom(float value)
        {
            m_Bottom = value;
            return *this;
        }

        Padding& Left(float value)
        {
            m_Left = value;
            return *this;
        }

        template <typename... Children>
        Padding& Add(Children... child)
        {
            (m_Children.push_back(ToWidget(child)), ...);
            return *this;
        }

        Ref<PaddingWidget> Build()
        {
            auto padding = CreateRef<PaddingWidget>(m_Top, m_Right, m_Bottom, m_Left);
            YGNodeStyleSetFlexGrow(padding->GetLayoutNode(), 1.0f);
            for (auto& child : m_Children)
            {
                padding->AddChild(child);
            }
            return padding;
        }

        operator Ref<PaddingWidget>() { return Build(); }
    };

    // ========== Container builder ==========
    template <typename... Children>
    inline Ref<ContainerWidget> Container(Children... child)
    {
        auto container = CreateRef<ContainerWidget>();
        YGNodeStyleSetFlexGrow(container->GetLayoutNode(), 1.0f);
        AddChildren(container, child...);
        return container;
    }

    // ========== Stack (Layout) builder - expands to fill space ==========
    template <typename... Children>
    inline Ref<LayoutWidget> Stack(LayoutDirection direction, Children... child)
    {
        auto stack = CreateRef<LayoutWidget>(direction);
        YGNodeStyleSetFlexGrow(stack->GetLayoutNode(), 1.0f);
        AddChildren(stack, child...);
        return stack;
    }

    // ========== Flex Stack - only uses needed space, aligns at start ==========
    template <typename... Children>
    inline Ref<LayoutWidget> FlexStack(LayoutDirection direction, Children... child)
    {
        auto stack = CreateRef<LayoutWidget>(direction);
        // Don't set flexGrow - only uses space needed
        YGNodeStyleSetAlignItems(stack->GetLayoutNode(), YGAlignFlexStart);
        AddChildren(stack, child...);
        return stack;
    }

    // ========== VStack - vertical flex stack (column, compact) ==========
    template <typename... Children>
    inline Ref<LayoutWidget> VStack(Children... child)
    {
        auto stack = CreateRef<LayoutWidget>(LayoutDirection::Column);
        YGNodeStyleSetAlignItems(stack->GetLayoutNode(), YGAlignFlexStart);
        AddChildren(stack, child...);
        return stack;
    }

    // ========== HStack - horizontal flex stack (row, compact) ==========
    template <typename... Children>
    inline Ref<LayoutWidget> HStack(Children... child)
    {
        auto stack = CreateRef<LayoutWidget>(LayoutDirection::Row);
        YGNodeStyleSetAlignItems(stack->GetLayoutNode(), YGAlignFlexStart);
        AddChildren(stack, child...);
        return stack;
    }

    // ========== Spacer - flexible space filler ==========
    inline Ref<ContainerWidget> Spacer()
    {
        auto spacer = CreateRef<ContainerWidget>();
        YGNodeStyleSetFlexGrow(spacer->GetLayoutNode(), 1.0f);
        return spacer;
    }

    inline Ref<ContainerWidget> Spacer(float size, LayoutDirection direction)
    {
        auto spacer = CreateRef<ContainerWidget>();
        if (direction == LayoutDirection::Row)
        {
            YGNodeStyleSetWidth(spacer->GetLayoutNode(), size);
        }
        else
        {
            YGNodeStyleSetHeight(spacer->GetLayoutNode(), size);
        }
        return spacer;
    }

    // ========== Text function returns Text ==========
} // namespace Skoga
