#include "Menu\Menu.h"
#include "ProyectUtilities\Utilities.h"
#include "ScreenManagements/Screen.h"


namespace menu
{
	struct Vector2
	{
		float x;
		float y;
	};
	struct Button
	{
		Vector2 RecPosition;
		int RecW;
		int RecH;
	

		const char* text = " ";
		Vector2 TextPosition;
		int size;
	};

	static Button title;
	static Button singlePlayer;
	static Button multiPlayer;
	static Button exit;

	static bool MouseMenuColision(float mousex, float mousey, float recx, float recy, float recw, float rech);

	void InitMenu()
	{

		title.RecPosition = { 400 / 2 - 180 , 20 };
		title.RecW = 350;
		title.RecH = 90;
		

		title.TextPosition = { 400 - 100, 50 };
		title.text = "VikoPong";
		title.size = 40;


		singlePlayer.RecPosition = { 400 - 325, 175 };
		singlePlayer.RecW = 250;
		singlePlayer.RecH = 90;
		

		singlePlayer.TextPosition = { 400 / 2 - 320, 200 };
		singlePlayer.text = "Single Mode";
		singlePlayer.size = 40;


		multiPlayer.RecPosition = { 400 + 65, 175 };
		multiPlayer.RecW = 250;
		multiPlayer.RecH = 90;
		

		multiPlayer.TextPosition = { 400 + 75, 200 };
		multiPlayer.text = "Multiplayer";
		multiPlayer.size = 40;


		exit.RecPosition = { 400 - 128, 350 };
		exit.RecW = 250;
		exit.RecH = 90;
		

		exit.TextPosition = { 400 - 40, 375 };
		exit.text = "Exit";
		exit.size = 40;

	}

	bool MouseMenuColision(float mousex, float mousey, float recx, float recy, float recw, float rech)
	{

		if (mousex >= recx &&
			mousex <= recx + recw &&
			mousey >= recy &&
			mousey <= recy + rech)
		{
			return true;
		}
		return false;
	}

	void MenuUpdate(Screen& currentScreen)
	{
		/*Vector2 mousePosition = GetMousePosition();*/


		/*if (MouseMenuColision(mousePosition.x, mousePosition.y, singlePlayer.RecPosition.x, singlePlayer.RecPosition.y, singlePlayer.RecW, singlePlayer.RecH))
		{
			singlePlayer.color = WHITE;

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				currentScreen = Screen::SinglePlayer;
				game::InitGame(currentScreen);
			}
		}
		else if (MouseMenuColision(mousePosition.x, mousePosition.y, multiPlayer.RecPosition.x, multiPlayer.RecPosition.y, multiPlayer.RecW, multiPlayer.RecH))
		{
			multiPlayer.color = WHITE;

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				currentScreen = Screen::MultiPlayer;
			}
		}
		else if (MouseMenuColision(mousePosition.x, mousePosition.y, exit.RecPosition.x, exit.RecPosition.y, exit.RecW, exit.RecH))
		{
			exit.color = WHITE;

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				currentScreen = Screen::Exit;
			}
		}
		else
		{
			singlePlayer.color = MAROON;
			multiPlayer.color = MAROON;
			exit.color = YELLOW;
		}*/


	}

	void MenuDrawing()
	{
		

		/*DrawRectangle(title.RecPosition.x, title.RecPosition.y, title.RecW, title.RecH, title.color);
		DrawRectangle(singlePlayer.RecPosition.x, singlePlayer.RecPosition.y, singlePlayer.RecW, singlePlayer.RecH, singlePlayer.color);
		DrawRectangle(multiPlayer.RecPosition.x, multiPlayer.RecPosition.y, multiPlayer.RecW, multiPlayer.RecH, multiPlayer.color);
		DrawRectangle(exit.RecPosition.x, exit.RecPosition.y, exit.RecW, exit.RecH, exit.color);

		DrawText("VikoPong", title.TextPosition.x, title.TextPosition.y, title.size, BLACK);
		DrawText("Single Mode", singlePlayer.TextPosition.x, singlePlayer.TextPosition.y, singlePlayer.size, BLACK);
		DrawText("Multiplayer", multiPlayer.TextPosition.x, multiPlayer.TextPosition.y, multiPlayer.size, BLACK);
		DrawText("Exit", exit.TextPosition.x, exit.TextPosition.y, exit.size, BLACK);*/
	}

}