#pragma once

#include "Skoga/Core.h"
#include "Skoga/Stylesheet.h"
#include "Skoga/Widget.h"
#include "Skoga/Widgets/Button.h"
#include "Skoga/Widgets/Container.h"
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

    // ========== StyleBuilder - Generic style-based container builder ==========
    class Box
    {
    private:
        Style m_Style;
        std::vector<Ref<Widget>> m_Children;

    public:
        template <typename... Children>
        explicit Box(Children... child)
        {
            (m_Children.push_back(ToWidget(child)), ...);
        }

        Box& BgColor(const Color& color)
        {
            m_Style.BackgroundColor = color;
            return *this;
        }

        Box& BorderColor(const Color& color)
        {
            m_Style.BorderColor = color;
            return *this;
        }

        Box& BorderRadius(float radius)
        {
            m_Style.BorderRadius = radius;
            return *this;
        }

        Box& Flex(float grow = 1.0f)
        {
            m_Style.FlexGrow = grow;
            return *this;
        }

        Box& FlexDirection(Skoga::FlexDirection dir)
        {
            m_Style.FlexDirection = dir;
            return *this;
        }

        Box& JustifyContent(Skoga::JustifyContent justify)
        {
            m_Style.JustifyContent = justify;
            return *this;
        }

        Box& AlignItems(Skoga::AlignItems align)
        {
            m_Style.AlignItems = align;
            return *this;
        }

        Box& Padding(float value)
        {
            m_Style.SetPadding(value);
            return *this;
        }

        Box& Padding(float vertical, float horizontal)
        {
            m_Style.SetPadding(vertical, horizontal);
            return *this;
        }

        Box& Padding(float top, float right, float bottom, float left)
        {
            m_Style.SetPadding(top, right, bottom, left);
            return *this;
        }

        Box& Margin(float value)
        {
            m_Style.SetMargin(value);
            return *this;
        }

        Box& Margin(float vertical, float horizontal)
        {
            m_Style.SetMargin(vertical, horizontal);
            return *this;
        }

        Box& Margin(float top, float right, float bottom, float left)
        {
            m_Style.SetMargin(top, right, bottom, left);
            return *this;
        }

        Box& Width(float width)
        {
            m_Style.Width = width;
            return *this;
        }

        Box& Height(float height)
        {
            m_Style.Height = height;
            return *this;
        }

        template <typename... Children>
        Box& Add(Children... child)
        {
            (m_Children.push_back(ToWidget(child)), ...);
            return *this;
        }

        Ref<ContainerWidget> Build()
        {
            auto box = CreateRef<ContainerWidget>();
            box->GetStyle() = m_Style;
            for (auto& child : m_Children)
            {
                box->AddChild(child);
            }
            box->ApplyStyle();
            return box;
        }

        operator Ref<ContainerWidget>() { return Build(); }
    };

    // ========== Text ==========
    class Text
    {
    private:
        const char* m_Text;
        HorizontalAlignment m_HAlign = HorizontalAlignment::Left;
        VerticalAlignment m_VAlign = VerticalAlignment::Top;

    public:
        explicit Text(const char* text) : m_Text(text) {}

        Text& Align(HorizontalAlignment hAlign, VerticalAlignment vAlign)
        {
            m_HAlign = hAlign;
            m_VAlign = vAlign;
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

        Ref<TextWidget> Build()
        {
            auto textWidget = CreateRef<TextWidget>(m_Text);
            textWidget->SetHorizontalAlignment(m_HAlign);
            textWidget->SetVerticalAlignment(m_VAlign);
            YGNodeStyleSetFlexGrow(textWidget->GetLayoutNode(), 1.0f);
            return textWidget;
        }

        operator Ref<TextWidget>() { return Build(); }
    };

    // ========== Button ==========
    class Button
    {
    private:
        std::vector<Ref<Widget>> m_Children;
        Widget::OnClickCallback m_OnClick;

    public:
        Button() = default;

        template <typename... Children>
        explicit Button(Children... child)
        {
            (m_Children.push_back(ToWidget(child)), ...);
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
            auto button = CreateRef<ButtonWidget>();
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

} // namespace Skoga

