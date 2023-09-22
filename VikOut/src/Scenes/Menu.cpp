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
		Vector2 TexturePosition;
		int SpriteW;
		int SpriteH;
	

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
		

		title.image = slLoadTexture("assets/jungle/PNG/menu/Title.png");
		title.TexturePosition = { 800 /2 , 800 -80 };
		title.SpriteW = 600;
		title.SpriteH = 600;
		

		title.TextPosition = { 800 / 2 , 800 - 80 };
		title.text = "VikOut";
		title.size = 40;


		singlePlayer.TexturePosition = { 400 - 325, 175 };
		singlePlayer.SpriteW = 250;
		singlePlayer.SpriteH = 90;
		

		singlePlayer.TextPosition = { 400 / 2 - 320, 200 };
		singlePlayer.text = "Single Mode";
		singlePlayer.size = 40;


		multiPlayer.TexturePosition = { 400 + 65, 175 };
		multiPlayer.SpriteW = 250;
		multiPlayer.SpriteH = 90;
		

		multiPlayer.TextPosition = { 400 + 75, 200 };
		multiPlayer.text = "Rules";
		multiPlayer.size = 40;


		exit.TexturePosition = { 400 - 128, 350 };
		exit.SpriteW = 250;
		exit.SpriteH = 90;
		

		exit.TextPosition = { 400 - 40, 375 };
		exit.text = "Exit";
		exit.size = 40;

	}

	bool MouseMenuColision(float mousex, float mousey, Button rec)
	{

		if (mousex >= rec.TexturePosition.x &&
			mousex <= rec.TexturePosition.x + rec.SpriteW &&
			mousey >= rec.TexturePosition.y &&
			mousey <= rec.TexturePosition.y + rec.SpriteH)
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
	int backGroundSprite = slLoadTexture("assets/jungle/PNG/menu/bg.png");

		slSprite(backGroundSprite,450,475, 900, 950);
		
		slSprite(title.image,title.TexturePosition.x, title.TexturePosition.y,title.SpriteW,title.SpriteH);
		
		/*slText( singlePlayer.TextPosition.x, singlePlayer.TextPosition.y, "Single Mode");
		slText( multiPlayer.TextPosition.x, multiPlayer.TextPosition.y, "Multiplayer");
		slText( exit.TextPosition.x, exit.TextPosition.y, "Exit");*/
	}

}