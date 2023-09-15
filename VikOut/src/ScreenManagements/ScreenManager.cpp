#include "ScreenManagements/ScreenManager.h"
#include "ScreenManagements/Screen.h"
#include "ProyectUtilities/Utilities.h"
#include "Menu/Menu.h"




namespace scenemanager
{
    Screen currentScreen;

	static void InitProgram();
	static void Update();
	static void Draw();
	static void Close();


	void RunProgram()
	{
		InitProgram();

		while (!slShouldClose() && currentScreen != Screen::Exit)
		{
			Update();
			Draw();
		}

		Close();
	}

    static void InitProgram()
    {
		int windowH = 850;
		int windowW = 800;

		slWindow(windowW, windowH, "VikOut", false);

        currentScreen = Screen::Game;

		menu::InitMenu();
		
    }
	
	static void Update()
	{

		switch (currentScreen)
		{
		case Screen::Menu:
			menu::MenuUpdate(currentScreen);
			break;
		case Screen::Game:
			
			break;
		case Screen::Exit:
			break;
		default:
			break;
		}
		
	}

	static void Draw()
	{
		

		switch (currentScreen)
		{
		case Screen::Menu:
			menu::MenuDrawing();
			break;
		case Screen::Game:
			
			break;
		case Screen::Exit:
			break;
		default:
			break;
		}

		
	}

	static void Close()
	{
		void slClose();
	}
}