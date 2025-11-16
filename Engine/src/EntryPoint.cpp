#include "EntryPoint.h"
#include "framework/Application.h"

int main ()
{
	Nonsense::Application* app = GetApplication();
    app->Run();
    delete app;
    
    return 0;
}