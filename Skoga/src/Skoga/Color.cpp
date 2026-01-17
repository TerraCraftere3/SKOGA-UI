#include "Color.h"
#include <algorithm>
#include <cmath>

namespace Skoga
{

    static float clampf(float v, float lo, float hi)
    {
        return std::max(lo, std::min(v, hi));
    }

    // Based on common wavelength to RGB approximation
    Color WavelengthToColor(float wavelengthNm)
    {
        float w = clampf(wavelengthNm, 380.0f, 780.0f);
        float R = 0.0f, G = 0.0f, B = 0.0f;

        if (w >= 380.0f && w < 440.0f)
        {
            R = -(w - 440.0f) / (440.0f - 380.0f);
            G = 0.0f;
            B = 1.0f;
        }
        else if (w >= 440.0f && w < 490.0f)
        {
            R = 0.0f;
            G = (w - 440.0f) / (490.0f - 440.0f);
            B = 1.0f;
        }
        else if (w >= 490.0f && w < 510.0f)
        {
            R = 0.0f;
            G = 1.0f;
            B = -(w - 510.0f) / (510.0f - 490.0f);
        }
        else if (w >= 510.0f && w < 580.0f)
        {
            R = (w - 510.0f) / (580.0f - 510.0f);
            G = 1.0f;
            B = 0.0f;
        }
        else if (w >= 580.0f && w < 645.0f)
        {
            R = 1.0f;
            G = -(w - 645.0f) / (645.0f - 580.0f);
            B = 0.0f;
        }
        else if (w >= 645.0f && w <= 780.0f)
        {
            R = 1.0f;
            G = 0.0f;
            B = 0.0f;
        }

        // Intensity factor to make edge wavelengths dimmer
        float factor = 1.0f;
        if (w > 700.0f)
        {
            factor = 0.3f + 0.7f * (780.0f - w) / (80.0f);
        }
        else if (w < 420.0f)
        {
            factor = 0.3f + 0.7f * (w - 380.0f) / (40.0f);
        }

        // Gamma correction
        float gamma = 0.8f;
        auto adjust = [factor, gamma](float c)
        {
            if (c <= 0.0f)
                return 0.0f;
            return static_cast<float>(std::pow(c * factor, gamma));
        };

        return Color(adjust(R), adjust(G), adjust(B), 1.0f);
    }

} // namespace Skoga
