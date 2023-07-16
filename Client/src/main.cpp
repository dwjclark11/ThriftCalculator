#define SDL_MAIN_HANDLED 1
#include <iostream>
#include "Application.h"

#ifdef _WIN32
#include <Windows.h>
bool HideConsole()
{
	return ShowWindow(GetConsoleWindow(), SW_HIDE);
}
#endif


int main()
{	
#ifdef NDEBUG 
	if (!HideConsole())
	{
		std::cout << "Failed to hide the console!" << std::endl;
	}
#endif

	try
	{
		auto& app = ThriftCalculator::Application::GetInstance();
		app.Run();
		
	}
	catch(TException& tx)
	{
		std::cout << "ERROR: " << tx.what() << std::endl;
	}

	return 0;
}