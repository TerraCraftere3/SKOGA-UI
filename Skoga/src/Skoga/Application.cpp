#include "Application.h"
#include "Config.h"
#include "DebugSidebar.h"
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
    static Widget* g_HoveredWidget = nullptr;
    static bool g_LastMouseButtonState = false;
    static bool g_ShowDebug = false;
    static bool g_LastF6State = false;
    static Application* g_ApplicationInstance = nullptr;

    Application::Application(Config* config)
    {
        g_ApplicationInstance = this;

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
        YGNodeStyleSetFlexDirection(m_RootWidget->GetLayoutNode(), YGFlexDirectionRow);

        // Create main container with horizontal layout (content + debug sidebar)
        m_MainContainer = CreateRef<RootWidget>();
        YGNodeStyleSetFlexDirection(m_MainContainer->GetLayoutNode(), YGFlexDirectionRow);
        YGNodeStyleSetFlexGrow(m_MainContainer->GetLayoutNode(), 1.0f);

        // Create debug sidebar
#ifdef SKOGA_DEBUG
        m_DebugSidebar = CreateRef<DebugSidebar>();
#endif

        // Create user widget
        m_UserWidget = CreateRef<RootWidget>();
        YGNodeStyleSetFlexGrow(m_UserWidget->GetLayoutNode(), 1.0f);

        m_RootWidget->AddChild(m_MainContainer);
    }

    Application::~Application()
    {
        if (m_VG)
        {
            nvgDeleteGL3(m_VG);
        }
        glfwDestroyWindow(m_Window);
        glfwTerminate();

        if (g_ApplicationInstance == this)
            g_ApplicationInstance = nullptr;
    }

    void Application::Run()
    {
        while (!glfwWindowShouldClose(m_Window))
        {
            ExecuteMainThreadQueue();
            glfwPollEvents();

            // Handle mouse input
            double mouseX, mouseY;
            glfwGetCursorPos(m_Window, &mouseX, &mouseY);

            // Perform hit testing
            Widget* hitWidget = m_RootWidget->HitTest(static_cast<float>(mouseX), static_cast<float>(mouseY));

            // Handle hover state changes
            if (hitWidget != g_HoveredWidget)
            {
                if (g_HoveredWidget)
                {
                    g_HoveredWidget->TriggerHover(false);
                }
                g_HoveredWidget = hitWidget;
                if (g_HoveredWidget)
                {
                    g_HoveredWidget->TriggerHover(true);
                }
            }

            // Handle mouse clicks (on state change from released to pressed)
            bool currentMouseButtonState = glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
            if (currentMouseButtonState && !g_LastMouseButtonState)
            {
                if (hitWidget)
                {
                    hitWidget->TriggerClick();
                }
            }
            g_LastMouseButtonState = currentMouseButtonState;

#ifdef SKOGA_DEBUG
            // Toggle debug panel on F6 key press (edge-triggered)
            bool currentF6State = glfwGetKey(m_Window, GLFW_KEY_F6) == GLFW_PRESS;
            if (currentF6State && !g_LastF6State)
            {
                m_ShowDebugPanel = !m_ShowDebugPanel;

                // Update layout based on debug panel state
                if (m_ShowDebugPanel)
                {
                    m_MainContainer->ClearChildren();
                    m_MainContainer->AddChild(m_UserWidget);
                    m_MainContainer->AddChild(m_DebugSidebar);
                }
                else
                {
                    m_MainContainer->ClearChildren();
                    m_MainContainer->AddChild(m_UserWidget);
                }
            }
            g_LastF6State = currentF6State;
#endif

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

#ifdef SKOGA_DEBUG
            if (m_ShowDebugPanel)
            {
                m_UserWidget->DrawDebug(m_VG);
                m_DebugSidebar->Draw(m_VG);
            }
            else
            {
                m_RootWidget->Draw(m_VG);
            }
#else
            m_RootWidget->Draw(m_VG);
#endif

            nvgEndFrame(m_VG);

            glfwSwapBuffers(m_Window);
        }
    }

    void Application::SetLayout(Ref<Widget> layout)
    {
        m_UserWidget = layout;
        m_MainContainer->ClearChildren();
        m_MainContainer->AddChild(m_UserWidget);
    }

    void Application::ExecuteMainThreadQueue()
    {
        std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);

        for (auto& func : m_MainThreadQueue)
            func();

        m_MainThreadQueue.clear();
    }

    void Application::SubmitToMainThread(const std::function<void()>& function)
    {
        std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);

        m_MainThreadQueue.emplace_back(function);
    }

    Application* Application::GetInstance()
    {
        return g_ApplicationInstance;
    }
} // namespace Skoga