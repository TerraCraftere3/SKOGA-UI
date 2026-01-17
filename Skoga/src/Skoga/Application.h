#pragma once

#include "Core.h"
#include "Widget.h"

struct GLFWwindow;
struct NVGcontext;

namespace Skoga
{
    struct Config;
    class DebugSidebar;

    class Application
    {
    public:
        Application(Config* config);
        ~Application();

        void Run();

        void SetLayout(Ref<Widget> layout);

    private:
        GLFWwindow* m_Window;
        NVGcontext* m_VG;
        Ref<Widget> m_RootWidget;
        Ref<Widget> m_MainContainer;
        Ref<Widget> m_UserWidget;
        Ref<DebugSidebar> m_DebugSidebar;
        bool m_ShowDebugPanel = false;
    };
} // namespace Skoga