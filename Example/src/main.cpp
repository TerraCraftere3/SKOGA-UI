#include <Skoga/Application.h>
#include <Skoga/Config.h>
#include <Skoga/WidgetBuilders.h>
#include <nanovg.h>

#include <memory>

int main()
{
    Skoga::Config config;
    config.WindowWidth = 1024;
    config.WindowHeight = 768;
    config.WindowTitle = "Skoga Widgets Demo";
    Skoga::Application app(&config);

    // clang-format off
    auto layout = Skoga::Container(
        Skoga::Stack(
            Skoga::Column,
            Skoga::Stack(
                Skoga::Row,
                Skoga::Background(0.0f, 1.0f, 0.0f, 1.0f,
                    Skoga::Text("Top-Left", 20.0f, Skoga::HorizontalAlignment::Left, Skoga::VerticalAlignment::Top)
                ),
                Skoga::Background(0.0f, 0.0f, 1.0f, 1.0f,
                    Skoga::Text("Top-Center", 20.0f, Skoga::HorizontalAlignment::Center, Skoga::VerticalAlignment::Top)
                )
            ),
            Skoga::Background(1.0f, 0.0f, 0.0f, 1.0f,
                Skoga::Text("Center-Middle", 24.0f, Skoga::HorizontalAlignment::Center, Skoga::VerticalAlignment::Middle)
            ),
            Skoga::Background(0.5f, 0.5f, 0.5f, 1.0f,
                Skoga::Text("Bottom-Right", 20.0f, Skoga::HorizontalAlignment::Right, Skoga::VerticalAlignment::Bottom)
            )
        )
    );
    // clang-format on

    auto root = app.GetRootWidget();
    root->AddChild(layout);

    app.Run();
}