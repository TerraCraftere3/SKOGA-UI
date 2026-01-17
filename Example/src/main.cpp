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
    config.WindowTitle = "Example Skoga Application";
    Skoga::Application app(&config);

    auto root = app.GetRootWidget();
    root->AddChild(Skoga::Container(
        Skoga::Stack(
            Skoga::Column,
            Skoga::Stack(
                Skoga::Row,
                Skoga::Background(0.0f, 1.0f, 0.0f, 1.0f),
                Skoga::Background(0.0f, 0.0f, 1.0f, 1.0f)
            ),
            Skoga::Background(1.0f, 0.0f, 0.0f, 1.0f)
        )
    ));

    app.Run();
}