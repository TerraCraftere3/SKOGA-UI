#include <Skoga/Application.h>
#include <Skoga/Config.h>
#include <Skoga/WidgetBuilders.h>
#include <nanovg.h>

#include <memory>

Skoga::Ref<Skoga::Widget> CreateTextAlignment()
{
    using namespace Skoga;

    // clang-format off
    auto alignmentContainer = Container(
        Background(Color(0.1f, 0.1f, 0.1f, 1.0f),
            Padding(20.0f,
                Stack(
                    Column,
                    Text("Top Left (Arial)", 
                        18.0f, 
                        Color(1.0f, 0.0f, 0.0f), 
                        FontArial, 
                        HorizontalAlignment::Left, 
                        VerticalAlignment::Top),
                    Text("Center Center (Consolas)", 
                        18.0f, 
                        Color(0.0f, 1.0f, 0.0f), 
                        FontConsolas, 
                        HorizontalAlignment::Center, 
                        VerticalAlignment::Middle),
                    Text("Bottom Right (Segoe UI)", 
                        18.0f, 
                        Color(0.0f, 0.0f, 1.0f), 
                        FontSegoeui, 
                        HorizontalAlignment::Right, 
                        VerticalAlignment::Bottom)
                )
            )
        )
    );
    // clang-format on

    return alignmentContainer;
}

Skoga::Ref<Skoga::Widget> CreateNestedBackgrounds()
{
    using namespace Skoga;

    // clang-format off
    auto nestedBackgrounds = Background(Color(0.2f, 0.2f, 0.4f, 1.0f),
        Padding(50.0f,
            Background(
                Color(0.4f, 0.4f, 0.6f, 1.0f),
                Padding(50.0f,
                    Background(
                        Color(0.6f, 0.6f, 0.8f, 1.0f),
                        Padding(50.0f,
                            Background(
                                Color(0.8f, 0.8f, 1.0f, 1.0f),
                                Text("Nested Background", 20.0f, Color(0.0f, 0.0f, 0.0f), HorizontalAlignment::Center, VerticalAlignment::Middle)
                            )
                        )
                    )
                )
            )
        )
    );
    // clang-format on

    return nestedBackgrounds;
}

Skoga::Ref<Skoga::Widget> CreateLayout()
{
    using namespace Skoga;

    // clang-format off
    auto layout = Container(
        Stack(
            Row,
            CreateTextAlignment(),
            CreateNestedBackgrounds()
        )
    );
    // clang-format on

    return layout;
}

int main()
{
    Skoga::Config config;
    config.WindowWidth = 1024;
    config.WindowHeight = 768;
    config.WindowTitle = "Skoga Widgets Demo";
    Skoga::Application app(&config);

    auto root = app.GetRootWidget();
    root->AddChild(CreateLayout());

    app.Run();
}