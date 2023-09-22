#include "ScreenManagements/ScreenManager.h"
#include "ScreenManagements/Screen.h"
#include "ProyectUtilities/Utilities.h"
#include "Scenes/Menu.h"




namespace scenemanager
{
	Screen currentScreen;

	static void InitProgram();
	static void Update();
	static void Draw();


	void RunProgram()
	{
		InitProgram();

		while (!slShouldClose() && currentScreen != Screen::Settings)
		{
			Update();
			Draw();

		}

		slClose();	
	}

	static void InitProgram()
	{
		int windowH = 950;
		int windowW = 900;


		slWindow(windowW, windowH, "VikOut", false);
		slSetTextAlign(SL_ALIGN_CENTER);

		currentScreen = Screen::Menu;

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
		case Screen::Rules:

			break;
		case Screen::Settings:

			break;
		case Screen::Exit:
			slClose();
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
		case Screen::Settings:
			break;
		default:
			break;
		}

		slRender();
	}

}