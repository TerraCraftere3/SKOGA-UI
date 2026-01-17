#pragma once

#include "Skoga/Core.h"
#include "Skoga/Widget.h"

namespace Skoga
{
    class DebugSidebar;

    Ref<Widget> CreateDebugOverlay(Ref<DebugSidebar> debugSidebar);
} // namespace Skoga