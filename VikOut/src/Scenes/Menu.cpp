#include "Scenes\Menu.h"
#include "ProyectUtilities\Utilities.h"
#include "ScreenManagements/Screen.h"
#include "ProyectUtilities/Colours.h"

namespace menu
{
	struct Vector2
	{
		double x;
		double y;
	};
	struct Button
	{
		Vector2 RecPosition;
		int RecW;
		int RecH;
	

		const char* text = " ";
		Vector2 TextPosition;
		int size;
		int image;
	};

	static Button title;
	static Button singlePlayer;
	static Button multiPlayer;
	static Button exit;

	static bool MouseMenuColision(float mousex, float mousey, Button rec);

	void InitMenu()
	{


		title.RecPosition = { 800 /2 , 800 -80 };
		title.RecW = 350;
		title.RecH = 90;
		

		title.TextPosition = { 800 / 2 , 800 - 80 };
		title.text = "VikOut";
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
		multiPlayer.text = "Rules";
		multiPlayer.size = 40;


		exit.RecPosition = { 400 - 128, 350 };
		exit.RecW = 250;
		exit.RecH = 90;
		

		exit.TextPosition = { 400 - 40, 375 };
		exit.text = "Exit";
		exit.size = 40;

	}

	bool MouseMenuColision(float mousex, float mousey, Button rec)
	{

		if (mousex >= rec.RecPosition.x &&
			mousex <= rec.RecPosition.x + rec.RecW &&
			mousey >= rec.RecPosition.y &&
			mousey <= rec.RecPosition.y + rec.RecH)
		{
			return true;
		}
		return false;
	}

	void MenuUpdate(Screen& currentScreen)
	{
		int mousePositionX = slGetMouseX();
		int mousePositionY = slGetMouseY();


	//	if (MouseMenuColision(mousePositionX, mousePositionY, singlePlayer))
	//	{
	//		singlePlayer.color = WHITE;

	//		if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
	//		{
	//			currentScreen = Screen::SinglePlayer;
	//			game::InitGame(currentScreen);
	//		}
	//	}
	//	else if (MouseMenuColision(mousePositionX, mousePositionY, multiPlayer))
	//	{
	//		multiPlayer.color = WHITE;

	//		if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
	//		{
	//			currentScreen = Screen::MultiPlayer;
	//		}
	//	}
	//	else if (MouseMenuColision(mousePositionX, mousePositionY, exit))
	//	{
	//		exit.color = WHITE;

	//		if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
	//		{
	//			currentScreen = Screen::Exit;
	//		}
	//	}
	//	else
	//	{
	//		singlePlayer.color = MAROON;
	//		multiPlayer.color = MAROON;
	//		exit.color = YELLOW;
	//	}


	}

	void MenuDrawing()
	{
		
		slSetForeColor(colors::RED.r, colors::RED.g, colors::RED.b, 1);
		slRectangleFill(title.RecPosition.x, title.RecPosition.y, title.RecW, title.RecH);
		
		slSetForeColor(colors::ORANGE.r, colors::ORANGE.g, colors::ORANGE.b, 1);
		slRectangleFill(singlePlayer.RecPosition.x, singlePlayer.RecPosition.y, singlePlayer.RecW, singlePlayer.RecH);
		
		slSetForeColor(colors::ORANGE.r, colors::ORANGE.g, colors::ORANGE.b, 0.5);
		slRectangleFill(multiPlayer.RecPosition.x, multiPlayer.RecPosition.y, multiPlayer.RecW, multiPlayer.RecH);
		
		slSetForeColor(colors::ORANGE.r, colors::ORANGE.g, colors::ORANGE.b, 1);
		slRectangleFill(exit.RecPosition.x, exit.RecPosition.y, exit.RecW, exit.RecH);

		slSetForeColor(colors::WHITE.r, colors::WHITE.g, colors::WHITE.b, 1);
		slSetFontSize(24);
		slText( title.TextPosition.x, title.TextPosition.y, "VikOut" );
		
		/*slText( singlePlayer.TextPosition.x, singlePlayer.TextPosition.y, "Single Mode");
		slText( multiPlayer.TextPosition.x, multiPlayer.TextPosition.y, "Multiplayer");
		slText( exit.TextPosition.x, exit.TextPosition.y, "Exit");*/
	}

}