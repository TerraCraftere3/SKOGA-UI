#pragma once

#include "Skoga/Color.h"
#include <yoga/Yoga.h>
#include <optional>

namespace Skoga
{
    enum class FlexDirection
    {
        Row,
        Column,
        RowReverse,
        ColumnReverse
    };

    enum class JustifyContent
    {
        FlexStart,
        Center,
        FlexEnd,
        SpaceBetween,
        SpaceAround,
        SpaceEvenly
    };

    enum class AlignItems
    {
        FlexStart,
        Center,
        FlexEnd,
        Stretch,
        Baseline
    };

    enum class Position
    {
        Relative,
        Absolute
    };

    // Core stylesheet class with CSS-like properties
    class Style
    {
    public:
        // Layout Properties (Flexbox)
        std::optional<FlexDirection> FlexDirection;
        std::optional<float> FlexGrow;
        std::optional<float> FlexShrink;
        std::optional<float> FlexBasis;
        std::optional<JustifyContent> JustifyContent;
        std::optional<AlignItems> AlignItems;
        std::optional<Position> Position;

        // Sizing
        std::optional<float> Width;
        std::optional<float> Height;
        std::optional<float> MinWidth;
        std::optional<float> MinHeight;
        std::optional<float> MaxWidth;
        std::optional<float> MaxHeight;

        // Spacing
        std::optional<float> MarginTop;
        std::optional<float> MarginRight;
        std::optional<float> MarginBottom;
        std::optional<float> MarginLeft;

        std::optional<float> PaddingTop;
        std::optional<float> PaddingRight;
        std::optional<float> PaddingBottom;
        std::optional<float> PaddingLeft;

        std::optional<float> BorderTop;
        std::optional<float> BorderRight;
        std::optional<float> BorderBottom;
        std::optional<float> BorderLeft;

        // Visual Properties
        std::optional<Color> BackgroundColor;
        std::optional<Color> BorderColor;
        std::optional<float> BorderRadius;
        std::optional<Color> TextColor;

        // Text Properties
        std::optional<float> FontSize;
        std::optional<const char*> FontFamily;

        // Utility methods
        void SetMargin(float value)
        {
            MarginTop = MarginRight = MarginBottom = MarginLeft = value;
        }

        void SetMargin(float vertical, float horizontal)
        {
            MarginTop = MarginBottom = vertical;
            MarginLeft = MarginRight = horizontal;
        }

        void SetMargin(float top, float right, float bottom, float left)
        {
            MarginTop = top;
            MarginRight = right;
            MarginBottom = bottom;
            MarginLeft = left;
        }

        void SetPadding(float value)
        {
            PaddingTop = PaddingRight = PaddingBottom = PaddingLeft = value;
        }

        void SetPadding(float vertical, float horizontal)
        {
            PaddingTop = PaddingBottom = vertical;
            PaddingLeft = PaddingRight = horizontal;
        }

        void SetPadding(float top, float right, float bottom, float left)
        {
            PaddingTop = top;
            PaddingRight = right;
            PaddingBottom = bottom;
            PaddingLeft = left;
        }

        void SetBorder(float value)
        {
            BorderTop = BorderRight = BorderBottom = BorderLeft = value;
        }

        void SetBorder(float vertical, float horizontal)
        {
            BorderTop = BorderBottom = vertical;
            BorderLeft = BorderRight = horizontal;
        }

        void SetBorder(float top, float right, float bottom, float left)
        {
            BorderTop = top;
            BorderRight = right;
            BorderBottom = bottom;
            BorderLeft = left;
        }
    };

    // Apply style to a Yoga node
    inline void ApplyStyle(YGNodeRef node, const Style& style)
    {
        if (style.FlexDirection.has_value())
        {
            YGFlexDirection direction;
            switch (style.FlexDirection.value())
            {
            case FlexDirection::Row:
                direction = YGFlexDirectionRow;
                break;
            case FlexDirection::Column:
                direction = YGFlexDirectionColumn;
                break;
            case FlexDirection::RowReverse:
                direction = YGFlexDirectionRowReverse;
                break;
            case FlexDirection::ColumnReverse:
                direction = YGFlexDirectionColumnReverse;
                break;
            }
            YGNodeStyleSetFlexDirection(node, direction);
        }

        if (style.FlexGrow.has_value())
            YGNodeStyleSetFlexGrow(node, style.FlexGrow.value());

        if (style.FlexShrink.has_value())
            YGNodeStyleSetFlexShrink(node, style.FlexShrink.value());

        if (style.FlexBasis.has_value())
            YGNodeStyleSetFlexBasis(node, style.FlexBasis.value());

        if (style.JustifyContent.has_value())
        {
            YGJustify justify;
            switch (style.JustifyContent.value())
            {
            case JustifyContent::FlexStart:
                justify = YGJustifyFlexStart;
                break;
            case JustifyContent::Center:
                justify = YGJustifyCenter;
                break;
            case JustifyContent::FlexEnd:
                justify = YGJustifyFlexEnd;
                break;
            case JustifyContent::SpaceBetween:
                justify = YGJustifySpaceBetween;
                break;
            case JustifyContent::SpaceAround:
                justify = YGJustifySpaceAround;
                break;
            case JustifyContent::SpaceEvenly:
                justify = YGJustifySpaceEvenly;
                break;
            }
            YGNodeStyleSetJustifyContent(node, justify);
        }

        if (style.AlignItems.has_value())
        {
            YGAlign align;
            switch (style.AlignItems.value())
            {
            case AlignItems::FlexStart:
                align = YGAlignFlexStart;
                break;
            case AlignItems::Center:
                align = YGAlignCenter;
                break;
            case AlignItems::FlexEnd:
                align = YGAlignFlexEnd;
                break;
            case AlignItems::Stretch:
                align = YGAlignStretch;
                break;
            case AlignItems::Baseline:
                align = YGAlignBaseline;
                break;
            }
            YGNodeStyleSetAlignItems(node, align);
        }

        if (style.Width.has_value())
            YGNodeStyleSetWidth(node, style.Width.value());

        if (style.Height.has_value())
            YGNodeStyleSetHeight(node, style.Height.value());

        if (style.MinWidth.has_value())
            YGNodeStyleSetMinWidth(node, style.MinWidth.value());

        if (style.MinHeight.has_value())
            YGNodeStyleSetMinHeight(node, style.MinHeight.value());

        if (style.MaxWidth.has_value())
            YGNodeStyleSetMaxWidth(node, style.MaxWidth.value());

        if (style.MaxHeight.has_value())
            YGNodeStyleSetMaxHeight(node, style.MaxHeight.value());

        if (style.MarginTop.has_value())
            YGNodeStyleSetMargin(node, YGEdgeTop, style.MarginTop.value());

        if (style.MarginRight.has_value())
            YGNodeStyleSetMargin(node, YGEdgeRight, style.MarginRight.value());

        if (style.MarginBottom.has_value())
            YGNodeStyleSetMargin(node, YGEdgeBottom, style.MarginBottom.value());

        if (style.MarginLeft.has_value())
            YGNodeStyleSetMargin(node, YGEdgeLeft, style.MarginLeft.value());

        if (style.PaddingTop.has_value())
            YGNodeStyleSetPadding(node, YGEdgeTop, style.PaddingTop.value());

        if (style.PaddingRight.has_value())
            YGNodeStyleSetPadding(node, YGEdgeRight, style.PaddingRight.value());

        if (style.PaddingBottom.has_value())
            YGNodeStyleSetPadding(node, YGEdgeBottom, style.PaddingBottom.value());

        if (style.PaddingLeft.has_value())
            YGNodeStyleSetPadding(node, YGEdgeLeft, style.PaddingLeft.value());
    }

} // namespace Skoga
