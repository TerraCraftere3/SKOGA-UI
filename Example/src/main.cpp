#include <Skoga/Application.h>
#include <Skoga/Config.h>
#include <Skoga/WidgetBuilders.h>
#include <nanovg.h>

#include <memory>

Skoga::Ref<Skoga::Widget> CreateTextAlignment()
{
    using namespace Skoga;

    // Create text with styling through stylesheet
    auto text1 = Text("Top Left (Arial)").Build();
    text1->GetStyle().FontSize = 18.0f;
    text1->GetStyle().TextColor = Red_500;
    text1->GetStyle().FontFamily = FontArial;

    auto text2 = Text("Center Center (Consolas)").Align(HorizontalAlignment::Center, VerticalAlignment::Middle).Build();
    text2->GetStyle().FontSize = 18.0f;
    text2->GetStyle().TextColor = Green_500;
    text2->GetStyle().FontFamily = FontConsolas;

    auto text3 = Text("Bottom Right (Segoe UI)").Align(HorizontalAlignment::Right, VerticalAlignment::Bottom).Build();
    text3->GetStyle().FontSize = 18.0f;
    text3->GetStyle().TextColor = Blue_500;
    text3->GetStyle().FontFamily = FontSegoeui;

    // clang-format off
    return Box()
        .BgColor(Gray_900)
        .Padding(20.0f)
        .FlexDirection(FlexDirection::Column)
        .JustifyContent(JustifyContent::SpaceEvenly)
        .Flex()
        .Add(text1, text2, text3)
        .Build();
    // clang-format on
}

Skoga::Ref<Skoga::Widget> CreateNestedBackgrounds()
{
    using namespace Skoga;

    // Create styled text
    auto nestedText = Text("Nested Background").Align(HorizontalAlignment::Center, VerticalAlignment::Middle).Build();
    nestedText->GetStyle().FontSize = 20.0f;
    nestedText->GetStyle().TextColor = Black;

    auto buttonText = Text("Click Me").Align(HorizontalAlignment::Center, VerticalAlignment::Middle).Build();
    buttonText->GetStyle().FontSize = 14.0f;
    buttonText->GetStyle().TextColor = Black;

    auto button = Button(buttonText).OnClick([]() { printf("Button Clicked!\n"); }).Build();
    button->GetStyle().BackgroundColor = Blue_700;
    button->GetStyle().BorderRadius = 5.0f;

    // clang-format off
    return Box()
        .BgColor(Blue_500)
        .Padding(50.0f)
        .Flex()
        .Add(
            Box()
                .BgColor(Blue_400)
                .Padding(50.0f)
                .Flex()
                .Add(
                    Box()
                        .BgColor(Blue_300)
                        .Padding(50.0f)
                        .Flex()
                        .Add(
                            Box()
                                .BgColor(Blue_200)
                                .BorderRadius(10.0f)
                                .Padding(20.0f)
                                .FlexDirection(Skoga::FlexDirection::Column)
                                .AlignItems(Skoga::AlignItems::Center)
                                .JustifyContent(Skoga::JustifyContent::Center)
                                .Add(nestedText, button)
                        )
                        .BorderRadius(15.0f)
                )
                .BorderRadius(20.0f)
        )
        .Build();
    // clang-format on
}

int main()
{
    Skoga::Config config;
    config.WindowWidth = 1824;
    config.WindowHeight = 768;
    config.WindowTitle = "Skoga Widgets Demo";
    Skoga::Application app(&config);

    // clang-format off
    app.SetLayout(Skoga::Box(
        Skoga::Box(
            CreateTextAlignment(),
            CreateNestedBackgrounds()
        ).FlexDirection(Skoga::FlexDirection::Row)
        .Flex()
    ).Build());
    // clang-format on

    app.Run();
}