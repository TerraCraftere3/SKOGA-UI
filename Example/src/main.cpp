#include <Skoga/Application.h>
#include <Skoga/Config.h>
#include <Skoga/File.h>
#include <Skoga/WidgetBuilders.h>
#include <nanovg.h>

#include <memory>

int main()
{
    Skoga::Config config;
    config.WindowWidth = 1824;
    config.WindowHeight = 768;
    config.WindowTitle = "Skoga Widgets Demo";
    Skoga::Application app(&config);

    app.SetLayout(Skoga::LoadFromFile("./main.xml"));

    app.Run();
}