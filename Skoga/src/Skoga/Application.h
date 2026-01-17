#pragma once

struct GLFWwindow;
struct NVGcontext;

namespace Skoga
{
    struct Config;

    class Application
    {
    public:
        Application(Config* config);
        ~Application();

        void Run();

    private:
        GLFWwindow* m_Window;
        NVGcontext* m_VG;
    };
} // namespace Skoga