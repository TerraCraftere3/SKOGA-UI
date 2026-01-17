#include <Skoga/Application.h>
#include <Skoga/Config.h>

int main()
{
    Skoga::Config config;
    config.WindowWidth = 1024;
    config.WindowHeight = 768;
    config.WindowTitle = "Example Skoga Application";
    Skoga::Application app(&config);
    app.Run();
}