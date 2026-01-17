#pragma once

struct GLFWwindow;

namespace Skoga{
    struct Config;

    class Application{
    public:
        Application(Config* config);
        ~Application();

        void Run();

    private:
        GLFWwindow* m_Window;
    };
}