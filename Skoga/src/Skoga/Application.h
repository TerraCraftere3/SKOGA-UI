#pragma once

#include "Core.h"
#include "Widget.h"

#include <functional>
#include <mutex>
#include <vector>

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
        void SubmitToMainThread(const std::function<void()>& function);

        static Application* GetInstance();

    private:
        void ExecuteMainThreadQueue();

    private:
        std::vector<std::function<void()>> m_MainThreadQueue;
        std::mutex m_MainThreadQueueMutex;
        GLFWwindow* m_Window;
        NVGcontext* m_VG;
        Ref<Widget> m_RootWidget;
        Ref<Widget> m_MainContainer;
        Ref<Widget> m_UserWidget;
        Ref<DebugSidebar> m_DebugSidebar;
        bool m_ShowDebugPanel = false;

        friend class DebugSidebar;
    };
} // namespace Skoga