#include <Skoga/Application.h>
#include <Skoga/Config.h>
#include <Skoga/Widget.h>
#include <Skoga/Widgets/Layout.h>
#include <nanovg.h>

#include <memory>

class ColorWidget : public Skoga::Widget
{
public:
    ColorWidget(float r, float g, float b) : m_R(r), m_G(g), m_B(b) {}

protected:
    void DrawSelf(NVGcontext* vg) override
    {
        nvgBeginPath(vg);
        nvgRect(vg, X(), Y(), Width(), Height());
        nvgFillColor(vg, nvgRGBAf(m_R, m_G, m_B, 1.0f));
        nvgFill(vg);
    }

private:
    float m_R, m_G, m_B;
};

int main()
{
    Skoga::Config config;
    config.WindowWidth = 1024;
    config.WindowHeight = 768;
    config.WindowTitle = "Example Skoga Application";
    Skoga::Application app(&config);

    auto root = app.GetRootWidget();

    auto stack = Skoga::CreateRef<Skoga::LayoutWidget>(Skoga::Column);
    YGNodeStyleSetFlexGrow(stack->GetLayoutNode(), 1.0f);
    root->AddChild(stack);

    auto row = Skoga::CreateRef<Skoga::LayoutWidget>(Skoga::Row);
    YGNodeStyleSetFlexGrow(row->GetLayoutNode(), 1.0f);
    stack->AddChild(row);

    auto redWidget = Skoga::CreateRef<ColorWidget>(1.0f, 0.0f, 0.0f);
    YGNodeStyleSetFlexGrow(redWidget->GetLayoutNode(), 1.0f);
    stack->AddChild(redWidget);

    auto greenWidget = Skoga::CreateRef<ColorWidget>(0.0f, 1.0f, 0.0f);
    YGNodeStyleSetFlexGrow(greenWidget->GetLayoutNode(), 1.0f);
    row->AddChild(greenWidget);

    auto blueWidget = Skoga::CreateRef<ColorWidget>(0.0f, 0.0f, 1.0f);
    YGNodeStyleSetFlexGrow(blueWidget->GetLayoutNode(), 1.0f);
    row->AddChild(blueWidget);

    app.Run();
}