#pragma once

namespace Skoga
{
    constexpr const char* FontSegoeui = "segoeui";
    constexpr const char* FontArial = "arial";
    constexpr const char* FontConsolas = "consolas";

    // Font management functions
    void LoadFont(const char* name, const char* filepath);
    void SetDefaultFont(const char* name);
} // namespace Skoga