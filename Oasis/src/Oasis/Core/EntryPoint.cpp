#include <iostream>

#include <Oasis/Core/Application.h>

extern Oasis::Application* CreateApplication();

int main()
{
	Oasis::Application* app = CreateApplication();
	app->Run();
	delete app;

	return 0;
}