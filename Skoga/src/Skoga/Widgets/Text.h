#pragma once

#include "Skoga/Widget.h"

namespace Skoga
{
    class TextWidget : public Widget
    {
    public:
        TextWidget(const char* text, float fontSize = 16.0f);

        void SetText(const char* text);
        void SetFontSize(float fontSize);

    protected:
        void DrawSelf(NVGcontext* vg) override;

    private:
        const char* m_Text;
        float m_FontSize;
    };
} // namespace Skoga