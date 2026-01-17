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
                    Text("Top Left (Arial)")
                        .FontSize(18.0f)
                        .Color(Red_500)
                        .Font(FontArial)
                        .Align(HorizontalAlignment::Left, VerticalAlignment::Top),
                    Text("Center Center (Consolas)")
                        .FontSize(18.0f)
                        .Color(Green_500)
                        .Font(FontConsolas)
                        .Align(HorizontalAlignment::Center, VerticalAlignment::Middle),
                    Text("Bottom Right (Segoe UI)")
                        .FontSize(18.0f)
                        .Color(Blue_500)
                        .Font(FontSegoeui)
                        .Align(HorizontalAlignment::Right, VerticalAlignment::Bottom)
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
    auto nestedBackgrounds = 
    Container(
    Background(Blue_500,
            Padding(
                50.0f,
                Background(
                    Blue_400,
                    Padding(
                        50.0f,
                        Background(
                            Blue_300,
                            Padding(
                                50.0f,
                                Background(
                                    Blue_200,
                                    Text("Nested Background")
                                        .FontSize(20.0f)
                                        .Color(Black)
                                        .Align(HorizontalAlignment::Center, VerticalAlignment::Middle)
                                ).CornerRadius(10.0f)
                            )
                        ).CornerRadius(15.0f)
                    )
                ).CornerRadius(20.0f)
            )
        )
    );
    // clang-format on

    return nestedBackgrounds;
}

int main()
{
    Skoga::Config config;
    config.WindowWidth = 1024;
    config.WindowHeight = 768;
    config.WindowTitle = "Skoga Widgets Demo";
    Skoga::Application app(&config);

    // clang-format off
    app.SetLayout(Skoga::Container(
        Skoga::Stack(
            Skoga::Row,
            CreateTextAlignment(),
            CreateNestedBackgrounds()
        )
    ));
    // clang-format on

    app.Run();
}