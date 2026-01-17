#include "Application.h"
#include "Config.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace Skoga
{
    Application::Application(Config* config)
    {
        if (!glfwInit())
        {
        }

        m_Window = glfwCreateWindow(config->WindowWidth, config->WindowHeight, config->WindowTitle, NULL, NULL);
        if (!m_Window)
        {
            glfwTerminate();
        }

        glfwMakeContextCurrent(m_Window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            glfwDestroyWindow(m_Window);
            m_Window = nullptr;
            glfwTerminate();
            return;
        }

        int fbWidth = 0, fbHeight = 0;
        glfwGetFramebufferSize(m_Window, &fbWidth, &fbHeight);
        glViewport(0, 0, fbWidth, fbHeight);

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    }

    Application::~Application()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void Application::Run()
    {
        while (!glfwWindowShouldClose(m_Window))
        {
            glfwPollEvents();

            int fbWidth = 0, fbHeight = 0;
            glfwGetFramebufferSize(m_Window, &fbWidth, &fbHeight);
            glViewport(0, 0, fbWidth, fbHeight);

            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(m_Window);
        }
    }
} // namespace Skoga