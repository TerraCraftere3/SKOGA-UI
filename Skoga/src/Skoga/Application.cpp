#include "Application.h"
#include "Config.h"
#include "Fonts.h"
#include "Widget.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <nanovg.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg_gl.h>
// clang-format on

namespace Skoga
{
    class RootWidget : public Widget
    {
    public:
        RootWidget() = default;
        virtual ~RootWidget() = default;

    protected:
        void DrawSelf(NVGcontext* vg) override {}
    };

    NVGcontext* g_VGContext = nullptr;

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
        g_VGContext = m_VG;
        if (!m_VG)
        {
            glfwDestroyWindow(m_Window);
            m_Window = nullptr;
            glfwTerminate();
            return;
        }

        // Load default Windows font
        LoadFont(FontSegoeui, "C:\\Windows\\Fonts\\segoeui.ttf");
        LoadFont(FontArial, "C:\\Windows\\Fonts\\arial.ttf");
        LoadFont(FontConsolas, "C:\\Windows\\Fonts\\consola.ttf");

        m_RootWidget = CreateRef<RootWidget>();

        YGNodeStyleSetWidth(m_RootWidget->GetLayoutNode(), config->WindowWidth);
        YGNodeStyleSetHeight(m_RootWidget->GetLayoutNode(), config->WindowHeight);
        YGNodeStyleSetFlexDirection(m_RootWidget->GetLayoutNode(), YGFlexDirectionColumn);
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

            int winWidth, winHeight;
            glfwGetWindowSize(m_Window, &winWidth, &winHeight);
            float pxRatio = (float)fbWidth / (float)winWidth;

            YGNodeStyleSetWidth(m_RootWidget->GetLayoutNode(), (float)winWidth);
            YGNodeStyleSetHeight(m_RootWidget->GetLayoutNode(), (float)winHeight);

            YGNodeCalculateLayout(m_RootWidget->GetLayoutNode(), (float)winWidth, (float)winHeight, YGDirectionLTR);
            m_RootWidget->OnLayout();

            nvgBeginFrame(m_VG, winWidth, winHeight, pxRatio);

            m_RootWidget->Draw(m_VG);

            nvgEndFrame(m_VG);

            glfwSwapBuffers(m_Window);
        }
    }

    void Application::SetLayout(Ref<Widget> layout)
    {
        m_RootWidget = layout;
    }
} // namespace Skoga