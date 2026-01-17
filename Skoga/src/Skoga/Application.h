#pragma once

struct GLFWwindow;
struct NVGcontext;

namespace Skoga
{
    struct Config;
    struct Widget;

    class Application
    {
    public:
        Application(Config* config);
        ~Application();

        void Run();

        // Root widget access
        Widget* GetRootWidget() const;

    private:
        GLFWwindow* m_Window;
        NVGcontext* m_VG;
        Widget* m_RootWidget;
    };
} // namespace Skoga