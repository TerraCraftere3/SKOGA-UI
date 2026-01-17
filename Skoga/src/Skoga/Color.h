#pragma once

namespace Skoga{
    struct Color
    {
        float R;
        float G;
        float B;
        float A;

        constexpr Color(float r, float g, float b, float a)
            : R(r), G(g), B(b), A(a)
        {
        }

        constexpr Color(float r, float g, float b)
            : R(r), G(g), B(b), A(1.0f)
        {
        }

        constexpr Color()
            : R(0.0f), G(0.0f), B(0.0f), A(1.0f)
        {
        }
    };

}