#include "Application.h"
#include "Config.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <nanovg.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg_gl.h>
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

        // Initialize NanoVG
        m_VG = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
        if (!m_VG)
        {
            glfwDestroyWindow(m_Window);
            m_Window = nullptr;
            glfwTerminate();
            return;
        }
    }

    Application::~Application()
    {
        if (m_VG)
        {
            nvgDeleteGL3(m_VG);
        }
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

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            // Get window size for proper scaling
            int winWidth, winHeight;
            glfwGetWindowSize(m_Window, &winWidth, &winHeight);
            float pxRatio = (float)fbWidth / (float)winWidth;

            // Begin NanoVG frame
            nvgBeginFrame(m_VG, winWidth, winHeight, pxRatio);

            // Draw a filled rectangle
            nvgBeginPath(m_VG);
            nvgRect(m_VG, 100, 100, 200, 150);
            nvgFillColor(m_VG, nvgRGBA(28, 130, 200, 255));
            nvgFill(m_VG);

            // Draw a circle
            nvgBeginPath(m_VG);
            nvgCircle(m_VG, 500, 150, 60);
            nvgFillColor(m_VG, nvgRGBA(220, 50, 100, 255));
            nvgFill(m_VG);

            // Draw a rounded rectangle with stroke
            nvgBeginPath(m_VG);
            nvgRoundedRect(m_VG, 100, 300, 250, 100, 10);
            nvgStrokeColor(m_VG, nvgRGBA(255, 200, 50, 255));
            nvgStrokeWidth(m_VG, 3.0f);
            nvgStroke(m_VG);
            nvgFillColor(m_VG, nvgRGBA(50, 50, 70, 200));
            nvgFill(m_VG);

            // Draw text (using default font)
            nvgFontSize(m_VG, 40.0f);
            nvgFontFace(m_VG, "sans");
            nvgFillColor(m_VG, nvgRGBA(255, 255, 255, 255));
            nvgText(m_VG, 150, 500, "Hello NanoVG!", NULL);

            // Draw a gradient
            NVGpaint gradient =
                nvgLinearGradient(m_VG, 400, 300, 600, 400, nvgRGBA(255, 100, 50, 255), nvgRGBA(50, 200, 255, 255));
            nvgBeginPath(m_VG);
            nvgRect(m_VG, 400, 300, 200, 100);
            nvgFillPaint(m_VG, gradient);
            nvgFill(m_VG);

            // End NanoVG frame
            nvgEndFrame(m_VG);

            glfwSwapBuffers(m_Window);
        }
    }
} // namespace Skoga