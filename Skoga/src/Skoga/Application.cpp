#include "Application.h"
#include "Config.h"

#include <GLFW/glfw3.h>

namespace Skoga{
    Application::Application(Config* config){
        if (!glfwInit()){
        }

        m_Window = glfwCreateWindow(config->WindowWidth, config->WindowHeight, config->WindowTitle, NULL, NULL);
        if (!m_Window){
            glfwTerminate();
        }

        glfwMakeContextCurrent(m_Window);
    }

    Application::~Application(){
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void Application::Run(){
        while (!glfwWindowShouldClose(m_Window)){
            glfwPollEvents();

            glfwSwapBuffers(m_Window);
        }
    }
}