#include "ScreenManagements/ScreenManager.h"

#include "ProyectUtilities/Utilities.h"
#include "ScreenManagements/Screen.h"
#include "Scenes/Credits.h"
#include "Scenes/Menu.h"
#include "Scenes/Game.h"
#include "Scenes/LevelSelector.h"



namespace scenemanager
{
	Screen currentScreen;

	static void InitProgram();
	static void Update();
	static void Draw();

	void RunProgram()
	{
		InitProgram();

		while (!slShouldClose() && currentScreen != Screen::Exit)
		{
			Update();
			Draw();
		}

		slClose();	
	}

	static void InitProgram()
	{
		int windowH = 950;
		int windowW = 1100;


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
			game::GameUpdate(currentScreen);
			break;
		case Screen::LevelSelector:
			levelSelector::LevelSelectorUpdate(currentScreen);
			break;
		case Screen::Credits:
			credits::CreditsUpdate(currentScreen);
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
			game::DrawGame(currentScreen);
			break;
		case Screen::LevelSelector:
			levelSelector::LevelSelectorDraw();
				break;
		case Screen::Credits:
			credits::CreditsDrawing();
			break;
		default:
			break;
		}

		slRender();
	}


}