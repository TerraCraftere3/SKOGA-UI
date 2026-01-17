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
        Background(Gray_900,
            Padding(20.0f,
                Stack(
                    Column,
                    Text("Top Left (Arial)", 
                        18.0f, 
                        Red_500, 
                        FontArial, 
                        HorizontalAlignment::Left, 
                        VerticalAlignment::Top),
                    Text("Center Center (Consolas)", 
                        18.0f, 
                        Green_500, 
                        FontConsolas, 
                        HorizontalAlignment::Center, 
                        VerticalAlignment::Middle),
                    Text("Bottom Right (Segoe UI)", 
                        18.0f, 
                        Blue_500, 
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
    auto nestedBackgrounds = Background(Blue_500,
        Padding(50.0f,
            Background(
                Blue_400,
                Padding(50.0f,
                    Background(
                        Blue_300,
                        Padding(50.0f,
                            Background(
                                Blue_200,
                                Text("Nested Background", 20.0f, Black, HorizontalAlignment::Center, VerticalAlignment::Middle)
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