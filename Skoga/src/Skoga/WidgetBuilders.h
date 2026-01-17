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

    // ========== TextBuilder ==========
    class TextBuilder
    {
    private:
        const char* m_Text;
        float m_FontSize = 16.0f;
        Color m_Color = Gray_100;
        const char* m_FontName = FontSegoeui;
        HorizontalAlignment m_HAlign = HorizontalAlignment::Left;
        VerticalAlignment m_VAlign = VerticalAlignment::Top;

    public:
        explicit TextBuilder(const char* text) : m_Text(text) {}

        TextBuilder& FontSize(float size)
        {
            m_FontSize = size;
            return *this;
        }

        TextBuilder& Color(const Skoga::Color& color)
        {
            m_Color = color;
            return *this;
        }

        TextBuilder& Font(const char* fontName)
        {
            m_FontName = fontName;
            return *this;
        }

        TextBuilder& HAlign(HorizontalAlignment align)
        {
            m_HAlign = align;
            return *this;
        }

        TextBuilder& VAlign(VerticalAlignment align)
        {
            m_VAlign = align;
            return *this;
        }

        TextBuilder& Align(HorizontalAlignment hAlign, VerticalAlignment vAlign)
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

    // ========== Stack (Layout) builder ==========
    template <typename... Children>
    inline Ref<LayoutWidget> Stack(LayoutDirection direction, Children... child)
    {
        auto stack = CreateRef<LayoutWidget>(direction);
        YGNodeStyleSetFlexGrow(stack->GetLayoutNode(), 1.0f);
        AddChildren(stack, child...);
        return stack;
    }

    // ========== Text function returns TextBuilder ==========
    inline TextBuilder Text(const char* text)
    {
        return TextBuilder(text);
    }
} // namespace Skoga
