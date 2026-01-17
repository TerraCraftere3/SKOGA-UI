#include "Fonts.h"

#include <nanovg.h>

namespace Skoga
{
    extern NVGcontext* g_VGContext;

    static NVGcontext* GetVGContext()
    {
        return Skoga::g_VGContext;
    }

    void LoadFont(const char* name, const char* filepath)
    {
        NVGcontext* vg = GetVGContext();
        if (vg)
        {
            nvgCreateFont(vg, name, filepath);
        }
    }

    void SetDefaultFont(const char* name)
    {
        NVGcontext* vg = GetVGContext();
        if (vg)
        {
            nvgFontFace(vg, name);
        }
    }

} // namespace Skoga