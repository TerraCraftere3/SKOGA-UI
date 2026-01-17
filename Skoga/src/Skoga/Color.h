#pragma once

namespace Skoga
{

    struct Color
    {
        float R;
        float G;
        float B;
        float A;

        constexpr Color(float r, float g, float b, float a) : R(r), G(g), B(b), A(a) {}

        constexpr Color(float r, float g, float b) : R(r), G(g), B(b), A(1.0f) {}

        constexpr Color() : R(0.0f), G(0.0f), B(0.0f), A(1.0f) {}
    };

    // White & Gray Scale (0-1 normalized)
    constexpr Color White = Color(1.0f, 1.0f, 1.0f);
    constexpr Color Gray_900 = Color(0.1f, 0.1f, 0.1f);
    constexpr Color Gray_800 = Color(0.15f, 0.15f, 0.15f);
    constexpr Color Gray_700 = Color(0.2f, 0.2f, 0.2f);
    constexpr Color Gray_600 = Color(0.3f, 0.3f, 0.3f);
    constexpr Color Gray_500 = Color(0.4f, 0.4f, 0.4f);
    constexpr Color Gray_400 = Color(0.6f, 0.6f, 0.6f);
    constexpr Color Gray_300 = Color(0.7f, 0.7f, 0.7f);
    constexpr Color Gray_200 = Color(0.8f, 0.8f, 0.8f);
    constexpr Color Gray_100 = Color(0.9f, 0.9f, 0.9f);
    constexpr Color Black = Color(0.0f, 0.0f, 0.0f);

    // Red Scale
    constexpr Color Red_900 = Color(0.42f, 0.08f, 0.08f);
    constexpr Color Red_800 = Color(0.55f, 0.11f, 0.11f);
    constexpr Color Red_700 = Color(0.64f, 0.12f, 0.12f);
    constexpr Color Red_600 = Color(0.73f, 0.16f, 0.16f);
    constexpr Color Red_500 = Color(0.96f, 0.26f, 0.21f);
    constexpr Color Red_400 = Color(0.98f, 0.47f, 0.43f);
    constexpr Color Red_300 = Color(0.99f, 0.60f, 0.55f);
    constexpr Color Red_200 = Color(0.99f, 0.74f, 0.70f);
    constexpr Color Red_100 = Color(1.0f, 0.88f, 0.87f);
    constexpr Color Red = Red_500;

    // Blue Scale
    constexpr Color Blue_900 = Color(0.08f, 0.18f, 0.42f);
    constexpr Color Blue_800 = Color(0.10f, 0.24f, 0.55f);
    constexpr Color Blue_700 = Color(0.12f, 0.30f, 0.64f);
    constexpr Color Blue_600 = Color(0.14f, 0.38f, 0.73f);
    constexpr Color Blue_500 = Color(0.22f, 0.47f, 0.97f);
    constexpr Color Blue_400 = Color(0.42f, 0.63f, 0.99f);
    constexpr Color Blue_300 = Color(0.54f, 0.70f, 0.99f);
    constexpr Color Blue_200 = Color(0.71f, 0.83f, 1.0f);
    constexpr Color Blue_100 = Color(0.87f, 0.92f, 1.0f);
    constexpr Color Blue = Blue_500;

    // Green Scale
    constexpr Color Green_900 = Color(0.08f, 0.42f, 0.12f);
    constexpr Color Green_800 = Color(0.10f, 0.55f, 0.15f);
    constexpr Color Green_700 = Color(0.11f, 0.64f, 0.15f);
    constexpr Color Green_600 = Color(0.14f, 0.73f, 0.18f);
    constexpr Color Green_500 = Color(0.25f, 0.96f, 0.24f);
    constexpr Color Green_400 = Color(0.48f, 0.98f, 0.43f);
    constexpr Color Green_300 = Color(0.60f, 0.99f, 0.55f);
    constexpr Color Green_200 = Color(0.74f, 0.99f, 0.70f);
    constexpr Color Green_100 = Color(0.88f, 1.0f, 0.87f);
    constexpr Color Green = Green_500;

    // Yellow Scale
    constexpr Color Yellow_900 = Color(0.42f, 0.38f, 0.05f);
    constexpr Color Yellow_800 = Color(0.55f, 0.48f, 0.06f);
    constexpr Color Yellow_700 = Color(0.64f, 0.56f, 0.07f);
    constexpr Color Yellow_600 = Color(0.73f, 0.66f, 0.12f);
    constexpr Color Yellow_500 = Color(0.96f, 0.82f, 0.15f);
    constexpr Color Yellow_400 = Color(0.99f, 0.89f, 0.40f);
    constexpr Color Yellow_300 = Color(0.99f, 0.93f, 0.57f);
    constexpr Color Yellow_200 = Color(1.0f, 0.96f, 0.72f);
    constexpr Color Yellow_100 = Color(1.0f, 0.99f, 0.88f);
    constexpr Color Yellow = Yellow_500;

    // Orange Scale
    constexpr Color Orange_900 = Color(0.42f, 0.20f, 0.05f);
    constexpr Color Orange_800 = Color(0.55f, 0.25f, 0.06f);
    constexpr Color Orange_700 = Color(0.64f, 0.30f, 0.07f);
    constexpr Color Orange_600 = Color(0.73f, 0.37f, 0.12f);
    constexpr Color Orange_500 = Color(0.96f, 0.53f, 0.16f);
    constexpr Color Orange_400 = Color(0.99f, 0.67f, 0.40f);
    constexpr Color Orange_300 = Color(0.99f, 0.76f, 0.57f);
    constexpr Color Orange_200 = Color(1.0f, 0.85f, 0.72f);
    constexpr Color Orange_100 = Color(1.0f, 0.93f, 0.88f);
    constexpr Color Orange = Orange_500;

    // Purple Scale
    constexpr Color Purple_900 = Color(0.34f, 0.12f, 0.42f);
    constexpr Color Purple_800 = Color(0.44f, 0.14f, 0.55f);
    constexpr Color Purple_700 = Color(0.52f, 0.15f, 0.64f);
    constexpr Color Purple_600 = Color(0.62f, 0.18f, 0.73f);
    constexpr Color Purple_500 = Color(0.81f, 0.30f, 0.96f);
    constexpr Color Purple_400 = Color(0.89f, 0.53f, 0.99f);
    constexpr Color Purple_300 = Color(0.93f, 0.67f, 0.99f);
    constexpr Color Purple_200 = Color(0.96f, 0.80f, 1.0f);
    constexpr Color Purple_100 = Color(0.98f, 0.90f, 1.0f);
    constexpr Color Purple = Purple_500;

    // Cyan Scale
    constexpr Color Cyan_900 = Color(0.08f, 0.38f, 0.42f);
    constexpr Color Cyan_800 = Color(0.10f, 0.50f, 0.55f);
    constexpr Color Cyan_700 = Color(0.11f, 0.59f, 0.64f);
    constexpr Color Cyan_600 = Color(0.14f, 0.68f, 0.73f);
    constexpr Color Cyan_500 = Color(0.15f, 0.88f, 0.96f);
    constexpr Color Cyan_400 = Color(0.40f, 0.94f, 0.99f);
    constexpr Color Cyan_300 = Color(0.57f, 0.97f, 1.0f);
    constexpr Color Cyan_200 = Color(0.72f, 0.99f, 1.0f);
    constexpr Color Cyan_100 = Color(0.88f, 1.0f, 1.0f);
    constexpr Color Cyan = Cyan_500;

    // Pink Scale
    constexpr Color Pink_900 = Color(0.40f, 0.12f, 0.28f);
    constexpr Color Pink_800 = Color(0.52f, 0.14f, 0.37f);
    constexpr Color Pink_700 = Color(0.61f, 0.15f, 0.43f);
    constexpr Color Pink_600 = Color(0.70f, 0.18f, 0.50f);
    constexpr Color Pink_500 = Color(0.92f, 0.30f, 0.67f);
    constexpr Color Pink_400 = Color(0.96f, 0.55f, 0.80f);
    constexpr Color Pink_300 = Color(0.98f, 0.69f, 0.87f);
    constexpr Color Pink_200 = Color(0.99f, 0.82f, 0.92f);
    constexpr Color Pink_100 = Color(1.0f, 0.91f, 0.96f);
    constexpr Color Pink = Pink_500;

    // Teal Scale
    constexpr Color Teal_900 = Color(0.08f, 0.36f, 0.34f);
    constexpr Color Teal_800 = Color(0.10f, 0.48f, 0.45f);
    constexpr Color Teal_700 = Color(0.11f, 0.57f, 0.53f);
    constexpr Color Teal_600 = Color(0.14f, 0.67f, 0.61f);
    constexpr Color Teal_500 = Color(0.25f, 0.88f, 0.82f);
    constexpr Color Teal_400 = Color(0.49f, 0.94f, 0.90f);
    constexpr Color Teal_300 = Color(0.61f, 0.97f, 0.94f);
    constexpr Color Teal_200 = Color(0.75f, 0.99f, 0.97f);
    constexpr Color Teal_100 = Color(0.89f, 1.0f, 0.99f);
    constexpr Color Teal = Teal_500;

    // Converts a wavelength in nanometers (approximately 380-780 nm)
    // to an sRGB color. Values outside the range will be clamped.
    Color WavelengthToColor(float wavelengthNm);

} // namespace Skoga