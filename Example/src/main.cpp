#include <Skoga/Application.h>
#include <Skoga/Config.h>
#include <Skoga/WidgetBuilders.h>
#include <nanovg.h>

#include <memory>

Skoga::Ref<Skoga::Widget> CreateTextAlignment()
{
    // clang-format off
    auto alignmentContainer = Skoga::Container(
        Skoga::Background(0.1f, 0.1f, 0.1f, 1.0f,
            Skoga::Padding(20.0f,
                Skoga::Stack(
                    Skoga::Column,
                    Skoga::Text("Top Left", 18.0f, Skoga::HorizontalAlignment::Left, Skoga::VerticalAlignment::Top),
                    Skoga::Text("Center Center", 18.0f, Skoga::HorizontalAlignment::Center, Skoga::VerticalAlignment::Middle),
                    Skoga::Text("Bottom Right", 18.0f, Skoga::HorizontalAlignment::Right, Skoga::VerticalAlignment::Bottom)
                )
            )
        )
    );
    // clang-format on

    return alignmentContainer;
}

Skoga::Ref<Skoga::Widget> CreateLayout()
{
    // clang-format off
    auto layout = Skoga::Container(
        Skoga::Stack(
            Skoga::Row,
            CreateTextAlignment(),
            Skoga::Background(0.2f, 0.2f, 0.4f, 1.0f,
                Skoga::Padding(50.0f,
                    Skoga::Background(0.4f, 0.4f, 0.8f, 1.0f,
                        Skoga::Padding(50.0f,
                            Skoga::Background(0.6f, 0.6f, 1.0f, 1.0f,
                                Skoga::Text("Nested Background", 20.0f, Skoga::HorizontalAlignment::Center, Skoga::VerticalAlignment::Middle)
                            )
                        )
                    )
                )
            )
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

    // clang-format off
    auto layout = CreateLayout();
    // clang-format on

    auto root = app.GetRootWidget();
    root->AddChild(layout);

    app.Run();
}