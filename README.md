# Skoga UI
## Usage
```cpp
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
    config.WindowTitle = "Example App";
    Skoga::Application app(&config);

    // clang-format off
    auto layout = Skoga::Container(
        Skoga::Stack(
            Skoga::Column,
            Skoga::Stack(
                Skoga::Row,
                Skoga::Background(0.0f, 1.0f, 0.0f, 1.0f),
                Skoga::Background(0.0f, 0.0f, 1.0f, 1.0f)
            ),
            Skoga::Background(1.0f, 0.0f, 0.0f, 1.0f)
        )
    );
    // clang-format on

    auto root = app.GetRootWidget();
    root->AddChild(layout);

    app.Run();
}
```
This program opens a window ***Example App*** and renders 3 Backgrounds in a Layout to the Screen