#include "Container.h"
#include <nanovg.h>
#include "Skoga/Stylesheet.h"

namespace Skoga
{
    ContainerWidget::ContainerWidget() {}

    void ContainerWidget::DrawSelf(NVGcontext* vg)
    {
        const auto& style = GetStyle();

        // Draw background if specified
        if (style.BackgroundColor.has_value())
        {
            const Color& bgColor = style.BackgroundColor.value();
            nvgFillColor(vg, nvgRGBAf(bgColor.R, bgColor.G, bgColor.B, bgColor.A));

            float radius = style.BorderRadius.has_value() ? style.BorderRadius.value() : 0.0f;
            nvgBeginPath(vg);
            nvgRoundedRect(vg, 0, 0, Width(), Height(), radius);
            nvgFill(vg);
        }

        // Draw border if specified
        if (style.BorderColor.has_value() && (style.BorderTop.has_value() || style.BorderRight.has_value() ||
                                              style.BorderBottom.has_value() || style.BorderLeft.has_value()))
        {
            const Color& borderColor = style.BorderColor.value();
            nvgStrokeColor(vg, nvgRGBAf(borderColor.R, borderColor.G, borderColor.B, borderColor.A));

            float borderWidth = style.BorderTop.value_or(1.0f);
            nvgStrokeWidth(vg, borderWidth);

            float radius = style.BorderRadius.has_value() ? style.BorderRadius.value() : 0.0f;
            nvgBeginPath(vg);
            nvgRoundedRect(vg, 0, 0, Width(), Height(), radius);
            nvgStroke(vg);
        }
    }
} // namespace Skoga